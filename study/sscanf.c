int main(int argc, char **argv){
	int iDelayTime = 0;
	printf("argc:%d\n",argc);
	if(argc >= 2)
	sscanf(argv[1], "%d", &iDelayTime);
	printf("%d\n", iDelayTime);
}
