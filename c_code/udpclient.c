#include<stdio.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<errno.h>

#define rport 3799

#define rip "10.50.123.52"

int main(int argc, char*argv[])
{

    int s,len;
    struct sockaddr_in addr;
    int addr_len;
    unsigned char msg[56]={0x01,0x01,'n','g',0x88,0x99,0xB1,0x99,0x99,0x9,0x99,0x99,0x99,0x99,0x99,0x99,0x99,0x99,'\0'};
    char ipstr[20] ={0};

    //memcpy(ipstr, argv[1],sizeof(ipstr));
    int i=0;
    if((s=socket(AF_INET,SOCK_DGRAM,0))<0)
    {
        perror("error");
        exit(1);
    }
    else
    {
        printf("socket created.\n");
        printf("socket id: %d\n",s);
        printf("romote ip: %s\n",rip);
        printf("remote port: %d\n",rport);
    }
    addr_len=sizeof(struct sockaddr_in);
    bzero(&addr,sizeof(addr));
    addr.sin_family=AF_INET;
    addr.sin_port=htons(rport);
    addr.sin_addr.s_addr=inet_addr(rip);
    struct sockaddr_in selfaddr;
    bzero(&selfaddr,sizeof(selfaddr));
    selfaddr.sin_family=AF_INET;
    selfaddr.sin_port=htons(1812);
    selfaddr.sin_addr.s_addr=htonl(INADDR_ANY);
    bind(s,(struct sockaddr*)&selfaddr,sizeof(struct sockaddr));
    while(1)
    {
        //bzero(msg,sizeof(msg));
        int aaa = 0;
        //          msg[5]='\0';
        len= sizeof(msg);
        aaa=sendto(s,msg,(size_t)len,0,(struct sockaddr*)&addr,addr_len);
        printf("\nInput message: %s len:%d aaa:%d\n error:%d \n",msg,len,aaa,errno);
        memset(msg, 0 ,sizeof(msg));
        len=recvfrom(s,msg,sizeof(msg),0,&addr,&addr_len);
        printf("\n%d :\n",i);
        i++;

        printf("\nreceived message: %s \n",msg);
        sleep(1);
        memset(msg,0, sizeof(msg));
        msg[4] = 0xB2;
    }
    return 0;
}
