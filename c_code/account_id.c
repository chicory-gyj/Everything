#include<stdio.h>
int main()
{
	unsigned int a;
	a = time(NULL);
	char b[2]={21,80};
	memcpy((char*)(&a)+2, b,2);
	printf("%x\n", a);
	return 0;
}
