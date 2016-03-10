#include <sys/socket.h>
#include <netinet/in.h>
#include<arpa/inet.h>

int main()
{
    unsigned char aucip[4];
    struct in_addr s;
    int itest;
    inet_pton(AF_INET, "192.168.1.1", (void *)&itest);
    inet_pton(AF_INET, "192.168.1.1", (void *)&s);
    inet_pton(AF_INET, "192.168.1.1", aucip);
    printf("%d\n", aucip[0]);
    printf("%d\n", aucip[3]*256*256*256 + aucip[2]*256*256 + aucip[1]*256 + aucip[0]);
    printf("itest:%d\n", itest);
    printf("in_addr.s_addr%d\n", s.s_addr);
    printf("%d\n", (s.s_addr && 0x0000ff00) >> 24);
    int ii = memcmp(&s.s_addr, aucip, 4);
    printf("cmp1: %d\n", ii);
    ii = memcmp(&itest, aucip, 4);
    printf("cmp2: %d\n", ii);

    struct in_addr aa;
    aa.s_addr = 3078823535;
    int ii = 3078823535;
    printf("%s\n",inet_ntoa((struct in_addr)ii));
}
