#include <stdio.h>
#include <time.h>
int main(void)
{
    struct tm *ptr;
    time_t lt;
    lt =time(NULL);
    ptr=localtime(&lt);
    char buff[70];
    strftime(buff, sizeof(buff), "%Y%m%d%H%M%S",ptr);
    printf("%s\n",buff);
    return 0;
}
