#include<stdio.h>
int main()
{
    char *p = NULL;
    p = malloc(1);
    free(p);
    if(p)
        printf("NOT NULL");
    else
        printf("NULL");
}
