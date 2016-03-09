#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include <netdb.h>
#include <stdio.h>
#include <string.h>

int main()
{
    struct addrinfo hints;
    struct addrinfo *result;
    struct addrinfo *rp;
    char *hostname = "www.baidu.com";
    int ret;

    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_family = AF_UNSPEC;    /*  Allow IPv4 or IPv6 */
    hints.ai_socktype = 1; /*  Datagram socket */
    hints.ai_flags = AI_PASSIVE;    /*  For wildcard IP address */
    hints.ai_protocol = 0;          /*  Any protocol */
    hints.ai_canonname = NULL;
    hints.ai_addr = NULL;
    hints.ai_next = NULL;

    ret = getaddrinfo(NULL, hostname, &hints, &result);
    if(ret != 0)
    {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(ret));
        exit(1);
    }

    for(rp = result; rp != NULL; rp = rp->ai_next)
    {
        struct sockaddr_in *ip = (struct sockaddr_in *)(rp->ai_addr);
        printf("ip:%d", ip->sin_addr.s_addr);
        char ipAddress[INET_ADDRSTRLEN];
        inet_ntop(AF_INET, &(ip->sin_addr), ipAddress, INET_ADDRSTRLEN);

        printf("The IP address is: %s\n", ipAddress);
    }

    if(rp == NULL)
    {
        fprintf(stderr, "Could not bind\n");
        exit(1);
    }

    freeaddrinfo(result);
}
