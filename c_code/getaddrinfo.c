#include<>
int main()
{
    struct addrinfo hints;
    struct addrinfo *result;
    struct addrinfo *rp;
    char *hostname = "www.baidu.com";
    int ret;

    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_family = AF_UNSPEC;    /*  Allow IPv4 or IPv6 */
    hints.ai_socktype = SOCK_DGRAM; /*  Datagram socket */
    hints.ai_flags = AI_PASSIVE;    /*  For wildcard IP address */
    hints.ai_protocol = 0;          /*  Any protocol */
    hints.ai_canonname = NULL;
    hints.ai_addr = NULL;
    hints.ai_next = NULL;

    ret = getaddrinfo(NULL, hostname, &hints, &result);
    if(ret != 0)
    {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(ret));
        exit(EXIT_FAILURE);
    }

    for(rp = result; rp != NULL; rp = rp->ai_next)
    {
        printf("ip:%d",rp->ai_addr);
    }

    if(rp == NULL)
    {
        fprintf(stderr, "Could not bind\n");
        exit(EXIT_FAILURE);
    }

    freeaddrinfo(result);
}
