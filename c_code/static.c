#include <stdio.h>
int func()
{
    static int hello;
    hello += 1;
    printf("%d",hello);
}

int main()
{
    func();
    func();
    func();
}
