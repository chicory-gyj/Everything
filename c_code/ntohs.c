#include<stdio.h>
int main()
{
	int i;
	unsigned char uchaha[10];
		uchaha[1] = 1;
		uchaha[3] = 1;
	int bb;
	memcpy(&bb,uchaha,4);
	bb = ntohl(bb);
	printf("%d\n",bb);
	

}
