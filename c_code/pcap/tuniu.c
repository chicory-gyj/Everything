#include <pcap.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <linux/ip.h>
#include <linux/tcp.h>
#include <linux/if_ether.h>
#define __init __attribute__ ((constructor(101)))

typedef unsigned int UINT16;
/* 1. 端口：80
 * 2. GET /__utm.gif?u中的utmp字段包含该虚拟id
 * */
int loc_pa_tuniu(const struct iphdr *pstIphdr, unsigned short usIphdrlen, const unsigned char *pkt, unsigned short len)
{
    const unsigned char *uiIpData;
    const struct ethhdr *pstEthhdr = NULL;
    const struct tcphdr *pstTcphdr = NULL;
    unsigned short tcphdrlen;
    const unsigned char *pTcpData = NULL;
    unsigned short usTcpDataLen;
    unsigned short dport, sport;
    const unsigned char *pucMac = NULL;

    if (NULL == pstIphdr || NULL == pkt )
    {
        return -1;
    }

    if (6 != pstIphdr->protocol) {
        return -1;
    }

    pstEthhdr = (struct ethhdr *)pkt;
    uiIpData = (unsigned char *)pstIphdr + usIphdrlen;
    pstTcphdr = (struct tcphdr *)uiIpData;
    tcphdrlen = pstTcphdr->doff << 2;
    pTcpData = ((unsigned char *)pstTcphdr + tcphdrlen);
    usTcpDataLen = ntohs(pstIphdr->tot_len) - usIphdrlen - tcphdrlen;

    dport = ntohs(pstTcphdr->dest);
    sport = ntohs(pstTcphdr->source);
    if(dport != 80)
    {
        return 0;
    }
    pucMac = pstEthhdr->h_dest;
    char vid[64] = {0};
    char *tuniu_dup = pTcpData;
    char *item;
    /* ios 和 andriod */
    if(!strncmp(tuniu_dup, "GET /__utm.gif", strlen("GET /__utm.gif")))
    {
        while((item = strsep(&tuniu_dup, "&")))
        {
            if(strstr(item, "utmp="))
            {
                printf("utmp:%s\n", item);
                item = item + (strlen(item) - 10);
                item = strstr(item ,"F");
                printf("vid:%s\n", item + 1);
            }
        }
    }
}
void __init init()
{
    printf("start...\n");
}
void callback(u_char *userless, const struct pcap_pkthdr* pkthdr, const u_char* packet)
{
    const struct ethhdr *ethernet = NULL;  /* The ethernet header [1] */
    const struct iphdr *pstIphdr;
    UINT16 usIphdrlen;

    ethernet = (struct ethhdr*)(packet);
    switch(htons(ethernet->h_proto))
    {
        case ETH_P_IP:
            pstIphdr = (struct iphdr*)(packet + sizeof(struct ethhdr));
            break;
        case ETH_P_8021Q:
            pstIphdr = (struct iphdr*)(packet + sizeof(struct ethhdr) + 2);
            break;
        default:
            break;
    }
    usIphdrlen = (pstIphdr->ihl<<2);
    if(0 == loc_pa_tuniu(pstIphdr, usIphdrlen, packet, pkthdr->caplen))
    {
    }
}

int main(int argc, char *argv[])
{
    pcap_t *handle;         /* Session handle */
    char *dev;          /* The device to sniff on */
    char errbuf[PCAP_ERRBUF_SIZE];  /* Error string */
    struct bpf_program fp;      /* The compiled filter */
    char filter_exp[] = "tcp port 80";  /* The filter expression */
    bpf_u_int32 mask;       /* Our netmask */
    bpf_u_int32 net;        /* Our IP */
    struct pcap_pkthdr header;  /* The header that pcap gives us */
    const u_char *packet;       /* The actual packet */

    /* Define the device */
    dev = pcap_lookupdev(errbuf);
    if (dev == NULL) {
        fprintf(stderr, "Couldn't find default device: %s\n", errbuf);
        return(2);
    }
    /* Find the properties for the device */
    if (pcap_lookupnet(dev, &net, &mask, errbuf) == -1) {
        fprintf(stderr, "Couldn't get netmask for device %s: %s\n", dev, errbuf);
        net = 0;
        mask = 0;
    }
    /* Open the session in promiscuous mode */
    handle = pcap_open_live("eth0", BUFSIZ, 1, 1000, errbuf);
    if (handle == NULL) {
        fprintf(stderr, "Couldn't open device %s: %s\n", dev, errbuf);
        return(2);
    }
    if (pcap_compile(handle, &fp, filter_exp, 0, net) == -1) {
        fprintf(stderr, "Couldn't parse filter %s: %s\n", filter_exp, pcap_geterr(handle));
        return(2);
    }
    if (pcap_setfilter(handle, &fp) == -1) {
        fprintf(stderr, "Couldn't install filter %s: %s\n", filter_exp, pcap_geterr(handle));
        return(2);
    }
    pcap_loop(handle, 0, callback, NULL);
    pcap_close(handle);
    return(0);
}
