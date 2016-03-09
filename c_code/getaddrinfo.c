#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include <netdb.h>
#include <stdio.h>
#include <string.h>

int main()
{
    struct addrinfo *result;
    struct addrinfo *rp;
    struct sockaddr_in *ip;
    char *hostname = "www.baidu.com";
    int ret;

    ret = getaddrinfo(hostname, NULL, NULL, &result);
    if(ret != 0)
    {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(ret));
        exit(1);
    }

    for(rp = result; rp != NULL; rp = rp->ai_next)
    {
        ip = (struct sockaddr_in *)(rp->ai_addr);
        printf("ip:%u\n", ip->sin_addr.s_addr);
        char ipAddress[INET_ADDRSTRLEN];
        inet_ntop(AF_INET, &(ip->sin_addr), ipAddress, INET_ADDRSTRLEN);

        printf("The IP address is: %s\n", ipAddress);
    }

    freeaddrinfo(result);
}
