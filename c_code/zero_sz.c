#include <stdio.h>
struct pack
{
    unsigned char a[4];
    unsigned char b[4];
    char c[0];
};

int main()
{
    unsigned char test[100] = "hello world 999";
    unsigned char *p = test;
    printf("size: %d\n", sizeof(struct pack));
    printf("len %d , %s\n",strlen(((struct pack *)p)->c), ((struct pack *)p)->c);
    char *filename = ((struct pack *)p)->c + 1;
    printf("filename :%s\n", filename);
    
}
