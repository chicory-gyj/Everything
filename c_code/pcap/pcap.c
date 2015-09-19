#include <pcap.h>
#include <stdio.h>
#define __init __attribute__ ((constructor(101)))
void __init init()
{
    printf("start...\n");
}
void callback(u_char *userless, const struct pcap_pkthdr* pkthdr, const u_char* packet)
{
    const u_char* tmp = packet;
    printf("mac:%x:%x:%x:%x:%x:%x\n",tmp[6],tmp[7],tmp[8],tmp[9],tmp[10],tmp[11]);
    printf("%x\n", tmp[42+0]);
    printf("%x%x\n", tmp[42+1], tmp[42+2]);
    printf("%x%x\n", tmp[42+3], tmp[42+4]);
    printf("%x%x\n", tmp[42+5], tmp[42+6]);
    printf("qq:%x%x%x%x\n",tmp[42+7], tmp[42+8], tmp[42+9], tmp[42+10]);  
}

int main(int argc, char *argv[])
{
    pcap_t *handle;         /* Session handle */
    char *dev;          /* The device to sniff on */
    char errbuf[PCAP_ERRBUF_SIZE];  /* Error string */
    struct bpf_program fp;      /* The compiled filter */
    char filter_exp[] = "port 8000";  /* The filter expression */
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
    handle = pcap_open_live("eth0 br0", BUFSIZ, 1, 1000, errbuf);
    if (handle == NULL) {
        fprintf(stderr, "Couldn't open device %s: %s\n", dev, errbuf);
        return(2);
    }
    /* Compile and apply the filter */
    if (pcap_compile(handle, &fp, filter_exp, 0, net) == -1) {
        fprintf(stderr, "Couldn't parse filter %s: %s\n", filter_exp, pcap_geterr(handle));
        return(2);
    }
    if (pcap_setfilter(handle, &fp) == -1) {
        fprintf(stderr, "Couldn't install filter %s: %s\n", filter_exp, pcap_geterr(handle));
        return(2);
    }
    /* Grab a packet */
    //packet = pcap_next(handle, &header);
    pcap_loop(handle, 0, callback, NULL);
    /* Print its length */
    //printf("Jacked a packet with length of [%d]\n", header.len);
    printf("%s",packet);
    /* And close the session */
    pcap_close(handle);
    return(0);
}
