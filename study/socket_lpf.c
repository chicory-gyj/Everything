#include <sys/types.h>
#include <sys/socket.h>
#include<netinet/in.h>
#include<errno.h>
#include<net/if.h>
#include <asm/types.h>
#include<linux/filter.h>

struct sock_filter dhcp_bpf_filter[] = {
	/* Make sure this is an IP packet... */
	BPF_STMT(BPF_LD + BPF_H + BPF_ABS, 12),
	BPF_JUMP(BPF_JMP + BPF_JEQ + BPF_K, 0x0800, 0, 8),

	/* Make sure it's a UDP packet... */
	BPF_STMT(BPF_LD + BPF_B + BPF_ABS, 23),
	BPF_JUMP(BPF_JMP + BPF_JEQ + BPF_K, IPPROTO_UDP, 0, 6),

	/* Make sure this isn't a fragment... */
	BPF_STMT(BPF_LD + BPF_H + BPF_ABS, 20),
	BPF_JUMP(BPF_JMP + BPF_JSET + BPF_K, 0x1fff, 4, 0),

	/* Get the IP header length... */
	BPF_STMT(BPF_LDX + BPF_B + BPF_MSH, 14),

	/* Make sure it's to the right port... */
	BPF_STMT(BPF_LD + BPF_H + BPF_IND, 16),
	BPF_JUMP(BPF_JMP + BPF_JEQ + BPF_K, 67, 0, 1),             /* patch */

	/* If we passed all the tests, ask for the whole packet. */
	BPF_STMT(BPF_RET+BPF_K, (u_int)-1),

	/* Otherwise, drop it. */
	BPF_STMT(BPF_RET+BPF_K, 0),
};

int main()
{
	int sock;
	struct sockaddr_in sa;
	if ((sock = socket(PF_PACKET, SOCK_PACKET,
			   htons(0x0003))) < 0)
	{
		printf("Creat Wrong\n");
	}
	memset (&sa, 0, sizeof(sa));
	sa.sin_family = AF_INET;
	//sa.sin_port = htons(5555);
	inet_pton(AF_INET,"0.0.0.0", &sa.sin_addr);
	memset(sa.sin_zero, 0 , sizeof(sa.sin_zero)); 	
	
	struct sockaddr skad = {0};
	skad.sa_family = AF_PACKET;
	struct ifreq ifq = {0};
	memcpy(ifq.ifr_name, "eth0",5);
	strncpy (skad.sa_data, (const char *)&ifq, sizeof(skad.sa_data));
	if (bind (sock, (struct sockaddr*)&skad, sizeof(struct sockaddr)) < 0)
		printf("Bind wrong : %d\n",errno);
	
	int dhcp_bpf_filter_len = sizeof(dhcp_bpf_filter)/sizeof(struct sock_filter);
	
	struct sock_fprog p;
	memset(&p, 0, sizeof(p));
	p.len = dhcp_bpf_filter_len;
	p.filter = dhcp_bpf_filter;
	dhcp_bpf_filter [8].k = ntohs ((short)999);
	if (setsockopt (sock, SOL_SOCKET, SO_ATTACH_FILTER, &p,
			sizeof(p)) < 0) 
	{
		printf("setsocket wrong: %d\n",errno);
	}
	int length = 0;
	unsigned char ibuf [1536];
	length = read(sock, ibuf, sizeof(ibuf));
	if (length <= 0)
	{
		printf("read wrong : %d\n",errno);
		return length;
	}
	else
	{
		printf("%x%x%x\n",ibuf[0],ibuf[1],ibuf[2]);
	};
	

	while(1)
	{
		sleep(1);
		printf("jin\n");
	}
	return 0
;
}
