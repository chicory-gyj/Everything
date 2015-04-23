#include<time.h>
#include<sys/types.h>
#include<sys/socket.h>
#include"eloop.h"
#include<netinet/in.h>
void test_print()
{
    time_t now = time(NULL);
    printf("secs %d\n", now);
    eloop_register_timeout(2,0,test_print,NULL,NULL);
}
int sock;
void socket_print()
{
    char buf[2000];
    int len = 100;
    recv(sock, buf, len, 0);
    printf("it's sock! buf:%s \n", buf);
}
void socket_register()
{
    struct sockaddr_in sock_addr;
    sock = socket(PF_INET, SOCK_DGRAM,0);
    sock_addr.sin_family = AF_INET;
    sock_addr.sin_port = htons(2222);
    sock_addr.sin_addr.s_addr = 0; 
    bind(sock, (struct sockaddr*)&sock_addr, sizeof(struct sockaddr));
    eloop_register_read_sock(sock, socket_print, NULL, NULL);
}
int main()
{
    eloop_init();
    eloop_register_timeout(2,0,test_print,NULL,NULL);
    socket_register();
    eloop_run();
    return;
}
