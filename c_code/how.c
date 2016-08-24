#include<stdio.h>
int main()
{
    char option230[255] = {0};

    int dhcp_option230_apmode = 3;
    char dhcp_option230_acurl[64] = "urltest";
    char dhcp_option230_ccsurl[64] = "ccstest";
    char dhcp_option230_hotspot[64] = "hotspot";
    char dhcp_option230_domain[64] = "domain";
    sprintf(option230,
            "\"APMODE=%s,"
            "AC_URL=%s,"
            "CCS_URL=%s,"
            "HOTSPOT=%s,"
            "DOMAIN=%s\"",
            (dhcp_option230_apmode == 1)?
            "fat":((dhcp_option230_apmode == 2) ? "fit":""),
            dhcp_option230_acurl,
            dhcp_option230_ccsurl,
            dhcp_option230_hotspot,
            dhcp_option230_domain);

    printf("%s\n", option230);

}

