#include<stdio.h>

int main ()
{
    struct {
        unsigned int p:3;
        unsigned int k:5;
        unsigned int a:2;
    }l;
    int c;
    for (c=0; c<20; ++c)
    {
        l.a=c;
        l.p=c;
        l.k=c;
        printf("%d\t%d\t%d\t%d\n",c,l.p,l.k,l.a);
    }
    return 0;
}
