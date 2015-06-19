#include <stdio.h>
#include <stdlib.h>
int main()
{
    srand((unsigned)time(NULL));
    int i = rand();
    int b = rand();
    printf("%d  %d\n",b,i);
}
