#include<stdlib.h>
#include<string.h>
#include<stdio.h>


char *getMemory(void)
{
    return (char *)malloc(100);
}


void main()
{
    char *str = NULL;
    str = getMemory();
    strcpy(str, "hello");
    printf("1:%s", str);
    free(str);
    printf("2:%s", str);
}

