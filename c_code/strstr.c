#include<stdio.h>
int main()
{
	int i =0;
	char *ch;
	char *ptr;
	char p[10] ="hello \n";
	ptr =p;
	printf("%d\n", strlen(p));
	printf("%s",p);
	ptr[strlen(p)-1]='\0';
//	printf("%s",p);
	for(i =0;i++;i<10)
	{
		printf(":%02X",ptr+i);
	}
	printf("=================");
	ch = strstr(p, "\n");
	ptr = p;
	ch = '\0';
	for(i =0;i++;i<10)
	{
		printf(":%02X",ptr+i);
	}
	printf("%s",p);
	return 0;
}
