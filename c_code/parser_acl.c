#include<stdio.h>
#include<netdb.h>
#include<netinet/in.h>

typedef struct{
    char szSrcIp[32];
    char szDstIp[32];
    char szSrcPort[8];
    char szDstPort[8];
    unsigned int uiType;      /* 协议类型（tcp/udp） */
    unsigned int uiAction;    /* 动作 */
}IM_ACL_T;

typedef struct{
    char szDomainName[256];
    char szPort[8];
    char szType[8];         /* 协议类型（tcp/udp） */
    char szAction[8];       /* 动作 */
}IM_DNS_T;
int addr_string_to_ip_string(const char *addr, char *ip, int len)
{
	struct hostent *he;
	struct in_addr h_addr, *in_addr_temp;

	if((he = gethostbyname(addr)) == NULL)
		return -1;

	in_addr_temp = (struct in_addr *)he->h_addr_list[0];
	h_addr.s_addr = in_addr_temp->s_addr;

	strncpy(ip, inet_ntoa(h_addr), len);

	return 0;
}
#if 0
int addr_string_to_ip_string(const char *addr, char *ip, int len)
{
	struct hostent *he;
	if((he = gethostbyname(addr)) == NULL)
		return -1;

    inet_ntop(he->h_addrtype, *he->h_addr_list, ip, sizeof(ip));


	return 0;
}
#endif
int is_ip_valid(char *ip)
{
    if(ip[0] == '*' && ip[1] == '\0')
    {
        ip[0] = '\0';
        return 0;
    }
	int n[4];
	char c[4];
	if (sscanf(ip, "%d%c%d%c%d%c%d%c",
		&n[0], &c[0], &n[1], &c[1],
		&n[2], &c[2], &n[3], &c[3]) == 7)
	{
		int i;
		for(i = 0; i < 3; ++i)
        {
			if (c[i] != '.')
			{
                printf("ip is illegal\n");
                return 1;
            }
		}
		for(i = 0; i < 4; ++i)
        {
			if (n[i] > 255 || n[i] < 0)
			{
                printf("ip is illegal\n");
                return 1;
            }
		}
		return 0;
	}
	else
	{
        printf("ip is illegal\n");
		return 1;
    }
}

int is_port_valid(char *port)
{
    if(port[0] == '*' && port[1] == '\0')
    {
        port[0] = '\0';
        return 0;
    }
    int n;
    for(n=0;port[n]!='\0';n++)
    {
        if(port[n]<'0' || port[n]>'9')
        {
            printf( "not port\n");
            return 1;
        }
    }
    return 0;
}
void ad_mirror_creat_dns_rule(char *acRule, IM_DNS_T stDns)
{
    int iRet = 0;
    char acPro[64] = {0};
    char acDomainName[64] = {0};
    char acIp[64] = {0};
    char acPort[64] = {0};
    if(atoi(stDns.szType)== 1)
    {
        strcpy(acPro,"udp");
    }
    else if(atoi(stDns.szType) == 2)
    {
        strcpy(acPro,"tcp");
    }

    strcpy(acDomainName,stDns.szDomainName);
    strcpy(acPort,stDns.szPort);

    //端口IP合法性检查
    iRet += is_port_valid(acPort);
    addr_string_to_ip_string(acDomainName,acIp,64);
    iRet += is_ip_valid(acIp);
    if(iRet != 0)
    {
        printf(
            "error = %d,acDomainName = [%s],acPort = [%s],acIp = [%s]\n",
            iRet,acDomainName,acPort,acIp);
        return ;
    }

    /* combin */
    if(acPro[0] != '\0')
    {
        sprintf(acRule,"%s",acPro);
    }
    if(acDomainName[0] != '\0')
    {
        if(acRule[0] != '\0')
        {
            sprintf(acRule,"%s and host %s",acRule,acDomainName);
        }
        else
        {
            sprintf(acRule,"host %s",acDomainName);
        }

    }
    if(acPort[0] != '\0')
    {
        if(acRule[0] != '\0')
        {
            sprintf(acRule,"%s and port %s",acRule,acPort);
        }
        else
        {
            sprintf(acRule,"port %s",acPort);
        }
    }
    return ;
}


void ad_mirror_creat_acl_rule(char *acRule, IM_ACL_T stAcl)
{
    int iRet = 0;
    char acPro[64] = {0};
    char acSrcIp[64] = {0};
    char acDstIp[64] = {0};
    char acSrcPort[64] = {0};
    char acDstPort[64] = {0};
    if(stAcl.uiType == 1)
    {
        strcpy(acPro,"udp");
    }
    else if(stAcl.uiType == 2)
    {
        strcpy(acPro,"tcp");
    }
    strcpy(acSrcIp,stAcl.szSrcIp);
    strcpy(acDstIp,stAcl.szDstIp);
    strcpy(acSrcPort,stAcl.szSrcPort);
    strcpy(acDstPort,stAcl.szDstPort);

    //端口IP合法性检查
    iRet += is_port_valid(acSrcPort);
    iRet += is_port_valid(acDstPort);
    iRet += is_ip_valid(acSrcIp);
    iRet += is_ip_valid(acDstIp);
    if(iRet != 0)
    {
        printf(
            "error = %d,acSrcIp = %s,acDstIp = %s,acSrcPort = %s,acDstPort = %s \n",
            iRet,acSrcIp,acDstIp,acSrcPort,acDstPort);
        return ;
    }

    /* combin */
    if(acPro[0] != '\0')
    {
        sprintf(acRule,"%s",acPro);
    }
    if(acSrcIp[0] != '\0')
    {
        if(acRule[0] != '\0')
        {
            sprintf(acRule,"%s and src host %s",acRule,acSrcIp);
        }
        else
        {
            sprintf(acRule,"src host %s",acSrcIp);
        }

    }
    if(acDstIp[0] != '\0')
    {
        if(acRule[0] != '\0')
        {
            sprintf(acRule,"%s and dst host %s",acRule,acDstIp);
        }
        else
        {
            sprintf(acRule,"dst host %s",acDstIp);
        }
    }
    if(acSrcPort[0] != '\0')
    {
        if(acRule[0] != '\0')
        {
            sprintf(acRule,"%s and src port %s",acRule,acSrcPort);
        }
        else
        {
            sprintf(acRule,"src port %s",acSrcPort);
        }
    }
    if(acDstPort[0] != '\0')
    {
        if(acRule[0] != '\0')
        {
            sprintf(acRule,"%s and dst port %s",acRule,acDstPort);
        }
        else
        {
            sprintf(acRule,"dst port %s",acDstPort);
        }
    }
    return ;
}

int parese_acl_to_expression(char *acl, char *expression)
{
    IM_ACL_T stImAcl;
    int acl_num = 0;
    int plus = 0;
    //plus = sprintf(&expression[plus], "%s", "'");
    char *pos;
    char *left;
    char *end;
    char pack[64];
    char unpack[128];
    pos = acl;
    end = acl;
    pos += strlen("acl=");
    printf("parse,%s\n", acl);
    for(pos; pos != NULL; pos = strstr(end,"<"))
    {
        end = strstr(pos, ">");
        memset(pack, 0 ,sizeof(pack));
        memset(unpack, 0, sizeof(unpack));
        memset(&stImAcl, 0 ,sizeof(stImAcl));
        strncpy(pack, pos+1, end - pos - 1);
        printf("%s\n", pack);
        sscanf(pack, "%[^,],%[^,],%[^,],%[^,],%d,%d",stImAcl.szSrcIp,stImAcl.szSrcPort,stImAcl.szDstIp,\
                stImAcl.szDstPort,&stImAcl.uiType,&stImAcl.uiAction);
        ad_mirror_creat_acl_rule(unpack, stImAcl);
        printf("%s, %d\n",unpack, strlen(unpack));
        if(strstr(expression, "(") == NULL)
        {
            plus += sprintf(&expression[plus], "(%s)", unpack);
        }
        else
        {
            plus += sprintf(&expression[plus], " or (%s)", unpack);
        }
        printf("%d, %d\n",plus, strlen(expression));
    }
}
int parese_dns_to_expression(char *dns, char *expression)
{
    IM_DNS_T stImDns;
    int dns_num = 0;
    int plus = strlen(expression);
    printf("plus: %d\n", plus);
    char *pos;
    char *left;
    char *end;
    char pack[64];
    char unpack[128];
    pos = dns;
    end = dns;
    pos += strlen("dns=");
    printf("parse,%s\n", dns);
    for(pos; pos != NULL; pos = strstr(end,"<"))
    {
        end = strstr(pos, ">");
        memset(pack, 0 ,sizeof(pack));
        memset(unpack, 0, sizeof(unpack));
        memset(&stImDns, 0 ,sizeof(stImDns));
        strncpy(pack, pos+1, end - pos - 1);
        sscanf(pack, "%[^,],%[^,],%[^,],%[^,]", stImDns.szDomainName, stImDns.szPort, stImDns.szType,\
        stImDns.szAction);

        ad_mirror_creat_dns_rule(unpack, stImDns);
        printf("%s, %d\n",unpack, strlen(unpack));
        if(strstr(expression, "(") == NULL)
        {
            plus += sprintf(&expression[plus], "(%s)", unpack);
        }
        else
        {
            plus += sprintf(&expression[plus], " or (%s)", unpack);
        }
        printf("%d, %d\n",plus, strlen(expression));
    }
}
int main()
{
        char *acl= "acl=<10.1.1.1,80,192.1.1.1,80,1,0>;<1.1.1.1,80,192.1.1.1,89,1,0>"; 
        char *dns= "dns=<web.chat.qq.com,*,80,2>";
        char expression[9800];
        parese_acl_to_expression(acl, expression);
        printf("%s\n",expression);
        parese_dns_to_expression(dns, expression);
        printf("%s\n",expression);

}


