#include<stdio.h>
#include<stdarg.h>
#include<stdlib.h>
int mon_log(char* format, ...)
{
	char str_tmp[1024];
	int i=0;
	va_list vArgList; 
	va_start(vArgList, format); 
	i = vsnprintf(str_tmp, 1024, format, vArgList);
	printf("%s\n",str_tmp); 
	printf("%s\n",format);
	printf("%s\n",vArgList);
	va_end(vArgList); 
	return i; 
}

int main()
{
       int i = mon_log("%s,%d,%d,%d","%E6%B6%88%E9%99%A4%E4%B9%8B%E6%98%9F%20pop%20star!",2,3,4);
}
