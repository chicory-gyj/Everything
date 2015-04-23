#include<stdio.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<errno.h>

int main(int argc, char*argv[])                                                                                                                                       
{
	struct sockaddr_in addr;
	struct sockaddr_in selfaddr = {0} ;
        int addr_len;
	int s;
	              
	if((s=socket(AF_INET,SOCK_DGRAM,0))<0)                                                                                                                  
	{   
		perror("error");                
		exit(1);
	}
	addr.sin_family = AF_INET ;
	addr.sin_addr.s_addr = inet_addr("127.0.0.1") ;
	addr.sin_port = htons(12345) ;

	selfaddr.sin_family = AF_INET ;
	selfaddr.sin_addr.s_addr = inet_addr("127.0.0.1") ;
	selfaddr.sin_port = htons(9999) ;
	memset(selfaddr.sin_zero, 0, sizeof(selfaddr.sin_zero));
	bind(s, (struct sockaddr*)&selfaddr, sizeof(selfaddr));

	if(sendto(s, "123456", 6, 0, (struct sockaddr*)&addr, sizeof(struct sockaddr)) < 0)
	{
		printf("send wrong!/n");
	}
}

