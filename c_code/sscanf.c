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

    char tuniu[1024] = "GET /__utm.gif?utmwv=5.4.4&utms=4&utmn=1629575272&utmhn=dynamic.m.tuniu.com&utme=8(5!UIWebview)9(5!true)&utmcs=UTF-8&utmsr=320x568&utmvp=320x504&utmsc=32-bit&utmul=zh-cn&utmje=0&utmfl=-&utmdt=%E9%80%94%E7%89%9B%E6%97%85%E6%B8%B8%E7%BD%91%E4%BC%9A%E5%91%98%E4%B8%AD%E5%BF%83_%E4%BC%9A%E5%91%98%E4%B8%AD%E5%BF%83_%E9%80%94%E7%89%9B%E6%97%85%E6%B8%B8%E7%BD%91&utmhid=1366638084&utmr=-&utmp=%2F%25E6%2597%25A0%25E7%25BA%25BF%2F%25E4%25BC%259A%25E5%2591%2598%25E4%25B8%25AD%25E5%25BF%2583%2F%25E8%25AE%25A2%25E5%258D%2595%2F39143336&utmht=1457778551401&utmac=UA-4782081-5&utmcc=__utma%3D1.1167300256.1457763541.1457769993.1457778317.3%3B%2B__utmz%3D1.1457763541.1.1.utmcsr%3D(direct)%7Cutmccn%3D(direct)%7Cutmcmd%3D(none)%3B&utmu=qXG~ HTTP/1.1";
    char vid[1024] = {0};
    char *tuniu_dup = tuniu;
    char *part;
    char *part_2;
    if(!strncmp(tuniu_dup, "GET /__utm.gif", strlen("GET /__utm.gif")))
    {
        while((part = strsep(&tuniu_dup, "&")))
        {
            while((part_2 = ))
        } 

    }
}
