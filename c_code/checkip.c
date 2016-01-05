#include <arpa/inet.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int invalid_ipaddr (char *str)
{
    if (str == NULL || *str == '\0')
        return 1;

    union
    {
        struct sockaddr addr;
        struct sockaddr_in6 addr6;
        struct sockaddr_in addr4;
    } a;
    memset (&a, 0, sizeof (a));
    if (1 == inet_pton (AF_INET, str, &a.addr4.sin_addr))
        return 0;
    else if (1 == inet_pton (AF_INET6, str, &a.addr6.sin6_addr))
        return 0;
    return 1;
}

int main(int argc, char *argv[])
{
    if(argc <2 )
    {
        printf("Useage %s IP\n", argv[0]);
        exit(1);
    }
    if((invalid_ipaddr(argv[1]) == 0))
    {
        printf("%s is ip\n", argv[1]);
    }
    else
    {
        printf("%s is invalid_ipadd \n",  argv[1]);
    }
}
