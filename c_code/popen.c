#include <stdio.h>
#include <string.h>
void get_subnet_front(char *subnet_front_list)
{
    FILE *file = popen("grep subnet dhcpd.conf"
            "  | awk '{print $2}' | sed 's/\\.0//g' | xargs",
            "r");
    fgets(subnet_front_list, 1024, file);
    printf("%s\n", subnet_front_list);


    int len = strlen(subnet_front_list);
    subnet_front_list[len - 1] = '\0';
    pclose(file);
}


int main()
{
#if 0
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
#endif
    char *subnet;
    char subnet_front_list[1024] = {0};

    get_subnet_front(subnet_front_list);
    char *subnet_list_copy = subnet_front_list;

    while ((subnet = strsep(&subnet_list_copy, " ")) != NULL) {
        if (!subnet)
            continue;
        printf("in side: %s\n", subnet);
    }
}
