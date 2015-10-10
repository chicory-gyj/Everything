#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
void mysendmsg()
{
    struct sockaddr_in receiver_addr;
    int sock_fd;
    char line[15] = "xxx";
    char line2[12] = "jjj";
    struct msghdr msg;
    struct iovec iov[2];
    sock_fd = socket(AF_INET,SOCK_DGRAM,IPPROTO_UDP);
    receiver_addr.sin_family = AF_INET;
    receiver_addr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
    receiver_addr.sin_port = htons(5000);
    msg.msg_name = &receiver_addr;
    msg.msg_namelen = sizeof(receiver_addr);
    msg.msg_iov = iov;
    msg.msg_iovlen = 2;
    msg.msg_iov[0].iov_base = line;
    msg.msg_iov[0].iov_len = strlen(line);
    msg.msg_iov[1].iov_base = line2;
    msg.msg_iov[1].iov_len = strlen(line2);
    msg.msg_control = 0;
    msg.msg_controllen = 0;
    msg.msg_flags = 0;
    sendmsg(sock_fd,&msg,0);
    close(sock_fd);
}
int main()
{
    mysendmsg();
}
