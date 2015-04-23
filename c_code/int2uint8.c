#include<stdio.h>
int main()
{
	unsigned char uchaha[2];
	int i = 4096;
	memcpy(uchaha, &i, sizeof(uchaha));
	printf("%d\n", uchaha[0]+uchaha[1]*256);
	char uu[10] ;
	uu[0] = 0x31;
	int b;
	b = atoi(uu);
	printf("%d\n",b);	
	return;
}
