#include <stdio.h>
int main()
{
    char absPath[256];
    strcat(absPath, getenv("WLCROOT"));
    strcat(absPath, "/etc/account.conf");
    printf("%s", absPath);
}
