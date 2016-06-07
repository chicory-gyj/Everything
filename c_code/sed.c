int main()
{
#define AUDIT_ZKXY_CONFIG_FILE "filter_zkxy.conf"
    char *seraddr = "11.11.11.11:9000";
    char addr[32] = {0};
    char port[32] = {0};
    char command[1024] = {0};
    sscanf(seraddr, "%[^:]:%[^:]", addr, port);
    printf("%s %s",addr,port);

    sprintf(command, "sed -i 's/parent_center_ip.*=.*/parent_center_ip=%s/' %s", addr, AUDIT_ZKXY_CONFIG_FILE);
    system(command);
    memset(command, 0, sizeof(command));
    sprintf(command, "sed -i 's/parent_center_port.*=.*/parent_center_port=%s/' %s", port, AUDIT_ZKXY_CONFIG_FILE);
    system(command);
    memset(command, 0, sizeof(command));
    sprintf(command, "sed -i 's/mirror_device_list.*=.*/mirror_device_list=%s/' %s", "sbssss", AUDIT_ZKXY_CONFIG_FILE);
    system(command);
    return 0;
}
