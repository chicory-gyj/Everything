#ifndef MAC_FMT
#define MAC_FMT "%02x:%02x:%02x:%02x:%02x:%02x"
#endif

#ifndef MAC_ARG
#define MAC_ARG(x) ((unsigned char*)(x))[0], ((unsigned char*)(x))[1], ((unsigned char*)(x))[2], ((unsigned char*)(x))[3], ((unsigned char*)(x))[4], ((unsigned char*)(x))[5]
#endif

#define MAC_ARG_S(x)  (&((x)[0])),(&((x)[1])),(&((x)[2])),(&((x)[3])),(&((x)[4])),(&((x)[5]))


int main(int argc, char **argv){
//	int iDelayTime = 0;
//	printf("argc:%d\n",argc);
//	if(argc >= 2)
//	sscanf(argv[1], "%d", &iDelayTime);
//	printf("%d\n", iDelayTime);
    unsigned char mac[6];
    sscanf("11:11:11:11:11:11", MAC_FMT, MAC_ARG_S(mac));
    printf(MAC_FMT, MAC_ARG(mac));
    char string[10] = "op=22";
    int ii;
    int result;
    result = sscanf(string, "op=%d", &ii);
    printf("result = %d\n", result);
    printf("i= %d\n", ii);

    char *dns = "*";
    unsigned char xi = sscanf(dns, "%hhu", &xi);
    printf("xi:%d\n", xi);
}
