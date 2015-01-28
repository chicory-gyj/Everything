#include <bits/sockaddr.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <net/if.h>
#include <linux/in.h>
#include <sys/ioctl.h>
#include <errno.h>

int main()
{
	unsigned char name[16] ="eth0";
	struct ifreq tmp;
	memset(&tmp, 0, sizeof(tmp));
	strcpy(tmp.ifr_name, name);
	
	int sock;
	sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	printf("sock : %d\n", sock);
	
	if ((errno = ioctl(sock, SIOCGIFADDR, &tmp)) < 0)
	{
		printf("ioctl fail! errno :%d\n",errno);
	}
	struct sockaddr sa;
	unsigned char ip[4];
	memcpy(sa.sa_data, tmp.ifr_addr.sa_data, sizeof(tmp.ifr_addr.sa_data));
	memcpy(ip, sa.sa_data+2, sizeof(ip));
	printf("%d.%d.%d.%d\n", ip[0],ip[1],ip[2],ip[3]);	
	return 0;
}
