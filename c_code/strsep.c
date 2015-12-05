#include <stdio.h>
#include <string.h>

int main()
{
    char client_list[1024] = "172.168.1.1|11:11:11:11:11;123|456";
    char *client_list_copy = strdup(client_list);
    char *item;
    char *ip_string;
    while((item = strsep(&client_list_copy, ";")))
    {
        if((ip_string = strsep(&item, "|")))
        {
            printf("ip:%s\n", ip_string);
            /*logout*/
        }
    }
    printf("client_list_copy, %s\n", client_list_copy);
/* need free */
}
