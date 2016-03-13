#include <pcap.h>
#include <stdio.h>
#define __init __attribute__ ((constructor(101)))

int loc_pa_tuniu(const struct iphdr *pstIphdr, unsigned short usIphdrlen, const unsigned char *pkt, unsigned short len)
{

}
void __init init()
{
    printf("start...\n");
}
void callback(u_char *userless, const struct pcap_pkthdr* pkthdr, const u_char* packet)
{
    const struct ethhdr *ethernet = NULL;  /* The ethernet header [1] */
    const struct packet_ip *ip;
    const struct packet_tcp *tcp;

    ethernet = (struct ethhdr*)(packet);
    switch(htons(ethernet->ether_type))
    {
        case 0X0800:
            ip = (struct packet_ip*)(packet + SIZE_ETHERNET);
            ip_head = IP_HL(ip)*4;
            if(ip_head < 20)
            {
                printf("无效的IP头长度: %u bytes", ip_head);
                return -1;
            }
            if(ip->ip_p == IPPROTO_TCP)
            {
                tcp = (struct packet_tcp*)(packet + SIZE_ETHERNET + ip_head);
                tcp_head = TH_OFF(tcp)*4;
                if (tcp_head < 20)
                {
                    printf("Invalid TCP head-length %u bytes", tcp_head);
                    return -1;
                }
            }
            break;
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
