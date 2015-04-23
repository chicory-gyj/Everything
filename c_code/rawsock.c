#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<linux/if_ether.h>
#include<linux/in.h>

int main()
{
	unsigned char buf[1600];
	
	int sock;
	if ((sock = socket(AF_INET, SOCK_RAW,  IPPROTO_UDP)) < 0) 
	{
		printf("sock fail\n");	
	}	
	
	while(1)
	{
		unsigned int len;
		int i;
		len = recv(sock, buf ,sizeof(buf), 0);
		printf("len = %d\n",len);
		for( i=0; i<len; i++)
		{
			printf("%02X:",buf[i]);
		}
		printf("\n");
	}

}
