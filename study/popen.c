#include <stdio.h>
#include <string.h>
int main()
{
	FILE *fpin;
	char line[32];
	if((fpin = popen("ifconfig eth0|grep 'inet addr'|awk '{print $2}'|awk -F: '{print $2}'", "r")) != NULL)
	{
		fgets(line, 32, fpin);
		int len = strlen(line);
		line[len - 1] = '\0';
		printf("%s", line);
	}
	pclose(fpin);
}
