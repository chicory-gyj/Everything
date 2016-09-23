/* fgets example */
#include <stdio.h>
#include <sys/select.h>

int check_fd_ok(int fd)
{
    fd_set rfds;
    struct timeval tv;
    int retval;

    tv.tv_sec = 5;
    tv.tv_usec = 0;

    FD_ZERO(&rfds);
    FD_SET(fd, &rfds);

    retval = select(fd + 1, &rfds, NULL, NULL, &tv);

    if (retval == -1) {
        perror("select()");
        goto ERR;
    }
    else if (retval) {
        printf("Data is available now.\n");
        return 1;
    } else {
        printf("No data within five seconds.\n");
        goto ERR;
    }
 ERR:
    return 0;
}

int main()
{
    FILE *pFile;
    char buf[100];
    int filno;

    printf("start\n");
    pFile = fopen("xx", "r");
    filno = fileno(pFile);
    int retval;

    do {
        retval = check_fd_ok(0);


        if (retval == -1)
            perror("select()");
        else if (retval) {
            printf("Data is available now.\n");
            if (fgets(buf, sizeof(buf), pFile) == NULL) {
                return -1;
            }
        }
        /* FD_ISSET(0, &rfds) will be true. */
        else
            printf("No data within five seconds.\n");
    } while(buf[3] == '-');
    printf("%s", buf);
    fclose(pFile);
    printf("end\n");
    return 0;
}
