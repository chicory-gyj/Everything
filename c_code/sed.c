int main()
{
    char *seraddr = "11.11.11.11:9000";
    char addr[32] = {0};
    char port[32] = {0};
    char command[1024] = {0};
    sscanf(seraddr, "%[^:]:%[^:]", addr, port);

    printf("%s %s",addr,port);
    //sprintf(command, "sed -i 's/parent_center_ip.*=.*/parent_center_ip=%s'", pstConf->acAuditServerAddr);
    //system(command);
}
