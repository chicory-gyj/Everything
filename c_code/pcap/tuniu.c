#include <pcap.h>
#include <stdio.h>
#define __init __attribute__ ((constructor(101)))

typedef unsigned int UINT16;
int loc_pa_tuniu(const struct iphdr *pstIphdr, unsigned short usIphdrlen, const unsigned char *pkt, unsigned short len)
{
    const unsigned char *uiIpData;
    const struct ethhdr *pstEthhdr = NULL;
    const struct tcphdr *pstTcphdr = NULL;
    unsigned short tcphdrlen;
    const unsigned char *pTcpData = NULL;
    unsigned short usTcpDataLen;
    unsigned short dport, sport;

    if (NULL == pstIphdr || NULL == pkt )
    {
        return -1;
    }

    if (IP_T_TCP != pstIphdr->protocol) {
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
}
void __init init()
{
    printf("start...\n");
}
void callback(u_char *userless, const struct pcap_pkthdr* pkthdr, const u_char* packet)
{
    const struct ethhdr *ethernet = NULL;  /* The ethernet header [1] */
    const struct iphdr *pstIphdr;
    const struct packet_tcp *tcp;
    UINT16 usIphdrlen;

    ethernet = (struct ethhdr*)(packet);
    switch(htons(ethernet->ether_type))
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
    usIphdrlen = (ip->ihl<<2);
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
