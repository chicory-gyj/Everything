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
    int len = pkthdr->len;
    //printf("caplen:%d\n", pkthdr->caplen);
    //printf("len:%d\n", pkthdr->len);
    if((tmp[42] == 0x02) && (tmp[len-1] == 0x03)) /*qq flag must be 0x02*/
    {
        printf("udp mac:%x:%x:%x:%x:%x:%x\n",tmp[6],tmp[7],tmp[8],tmp[9],tmp[10],tmp[11]);/*user mac*/
        //printf("%x\n", tmp[42+0]); /*flag*/
        //printf("%x%x\n", tmp[42+1], tmp[42+2]);/*version*/
        //printf("%x%x\n", tmp[42+3], tmp[42+4]);/*command*/
        //printf("%x%x\n", tmp[42+5], tmp[42+6]);/*squence*/
        printf("udp qq:%x%x%x%x\n",tmp[42+7], tmp[42+8], tmp[42+9], tmp[42+10]);  /*qq number*/
    }
    else if((tmp[68] == 0x02) && (tmp[len-1] == 0x03))
    {
        printf("tcp mac:%x:%x:%x:%x:%x:%x\n",tmp[6],tmp[7],tmp[8],tmp[9],tmp[10],tmp[11]);/* user mac*/
        printf("tcp qq:%x%x%x%x\n",tmp[68+7], tmp[68+8], tmp[68+9], tmp[68+10]);  /* qq number*/
    }
    else if((tmp[54]==0)&&(tmp[55]==0)&&(tmp[58]==0)&&(tmp[59]==0)&&(tmp[60]==0)&&(tmp[61]==0x09)&&(tmp[62]==0x01)&&(tmp[63]==0))
    {
        int qq_len = tmp[71] - 4;
        printf("android qq_len:%d\n",qq_len);
        printf("android tcp mac:%x:%x:%x:%x:%x:%x\n",tmp[6],tmp[7],tmp[8],tmp[9],tmp[10],tmp[11]);/* user mac*/
        printf("android qq:%.*s\n", qq_len, tmp+72);
    }
    else if((tmp[54]==0)&&(tmp[55]==0)&&(tmp[58]==0)&&(tmp[59]==0)&&(tmp[60]==0)&&(tmp[61]==0x08)&&(tmp[62]==0x01)&&(tmp[63]==0))
    {
        int ios_len = tmp[135] - 4;
        printf("ios qq_len:%d\n",ios_len);
        printf("ios tcp mac:%x:%x:%x:%x:%x:%x\n",tmp[6],tmp[7],tmp[8],tmp[9],tmp[10],tmp[11]);/* user mac*/
        printf("ios qq:%.*s\n", ios_len, tmp+136);
    }
}

int main(int argc, char *argv[])
{
    pcap_t *handle;         /* Session handle */
    char *dev;          /* The device to sniff on */
    char errbuf[PCAP_ERRBUF_SIZE];  /* Error string */
    struct bpf_program fp;      /* The compiled filter */
    char filter_exp[] = "udp dst port 8000 or tcp dst port 443 or tcp dst port 8080";  /* The filter expression */
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
    handle = pcap_open_live("eth5", BUFSIZ, 1, 1000, errbuf);
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
    //printf("%s",packet);
    /* And close the session */
    pcap_close(handle);
    return(0);
}
