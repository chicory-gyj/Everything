#ifndef MAC_FMT
#define MAC_FMT "%02x:%02x:%02x:%02x:%02x:%02x"
#endif

#ifndef MAC_ARG
#define MAC_ARG(x) ((unsigned char*)(x))[0], ((unsigned char*)(x))[1], ((unsigned char*)(x))[2], ((unsigned char*)(x))[3], ((unsigned char*)(x))[4], ((unsigned char*)(x))[5]
#endif

#define MAC_ARG_S(x)  (&((x)[0])),(&((x)[1])),(&((x)[2])),(&((x)[3])),(&((x)[4])),(&((x)[5]))
typedef struct
{
    char *acl;
}LIST;


int main(int argc, char **argv){
//	int iDelayTime = 0;
//	printf("argc:%d\n",argc);
//	if(argc >= 2)
//	sscanf(argv[1], "%d", &iDelayTime);
//	printf("%d\n", iDelayTime);
    unsigned char mac[6];
    sscanf("11:11:11:11:11:11", MAC_FMT, MAC_ARG_S(mac));
    printf(MAC_FMT, MAC_ARG(mac));
    char string[10] = "op=";
    int ii = 0;
    int result;
    result = sscanf(string, "op=%d", &ii);
    printf("result = %d\n", result);
    printf("i= %d\n", ii);

    char *dns = "*";
    unsigned char xi = sscanf(dns, "%hhu", &xi);
    printf("xi:%d\n", xi);

    char *item = "op=";
    char *temp = (char *)malloc(strlen(item));
    sscanf(item, "op=%s", temp);
    printf("op=%s",temp);


    char *haha;
    haha = (char *)malloc(sizeof(haha));
    memset(haha, 0, sizeof(haha));
    if(haha)
    printf("\nhaha =%s\n", haha);

    LIST *aaa;
    aaa = (LIST *)malloc(sizeof(LIST));
    memset(aaa, 0, sizeof(LIST));
    printf("acl = %s", aaa->acl);
    char tuniu[1024] = "GET /api/archive/mam/m189788671/0/0";
    char vid[1024] = {0};
    char *tuniu_dup = tuniu;
    char *item;
    if(!strncmp(tuniu_dup, tuniu, strlen(tuniu)))
    {
        while((item = strsep(&tuniu_dup, "&")))
        {
            if(strstr(item, "utmp="))
            {
                printf("utmp:%s\n", item);
                item = item + (strlen(item) - 10);
                item = strstr(item ,"F");
                printf("vid:%s\n", item + 1);
            }
        } 

    }
}
