#include<stdio.h>  
#include<stdlib.h>  
#include<string.h>  
#include<errno.h>  
#include<sys/types.h>  
#include<sys/socket.h>  
#include<netinet/in.h>  

#define IP_FMT	"%d.%d.%d.%d"
//#define IP_ARG(x) ((unsigned char*)(x)[0], (unsigned char*)(x)[1], (unsigned char*)(x)[2], (unsigned char*)(x)[3]
#define MY_PORT 9000

void my_inet_addr(char *pcStr, unsigned int *IpAddr)
{
    unsigned int ulDstIp[4]={0};
    char ucaTmpStr[32] = "127.0.0.1";
    printf("%s \n",pcStr);
    sscanf(ucaTmpStr,"%d.%d.%d.%d",&ulDstIp[0],&ulDstIp[1],&ulDstIp[2],&ulDstIp[3]);
   // printf("%s dst ip is :"IP_FMT"\n",__FUNCTION__,IP_ARG(ulDstIp));
    printf("%d %d %d %d\n",ulDstIp[0],ulDstIp[1],ulDstIp[2],ulDstIp[3]);
    memcpy(IpAddr,ulDstIp,4);
}
int main(int argc,char **argv)
{
    unsigned int uiMyaddrIp = 0;
    int iSockId;
    unsigned long aucBrIp[32] = {0};
     unsigned char aucip[32] = {0};
    char cSendBuff[20];
    struct sockaddr_in myaddr;
    memset(&myaddr,0,sizeof(myaddr));
    iSockId = socket(AF_INET,SOCK_DGRAM,0);
    if( iSockId < 0 )
    {
        printf("socket create fail\n");
        exit(0);
    }
   // my_inet_addr(argv[1],&uiMyaddrIp);
    myaddr.sin_family = AF_INET;
    myaddr.sin_port = htons(MY_PORT);
   // myaddr.sin_addr.s_addr = htonl(uiMyaddrIp);
   // inet_ntop(AF_INET, (void *)&uiMyaddrIp, aucip, 32);
    printf("%s\n",aucip);
    myaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
   // printf("receive the dst ip is :"IP_FMT"\n",IP_ARG(&myaddr.sin_addr.s_addr));
    printf("please input what are you send:\n");
    scanf("%s",cSendBuff);
    if((sendto(iSockId,cSendBuff,20,0,(struct sockaddr *)&myaddr,sizeof(myaddr))) < 0)
    {
        printf("send fail\n");
    }
    close(iSockId);
    return 0;
    
}

