#define SMP_CACHE_BYTES 16
#define SKB_DATA_ALIGN(X)	(((X) + (SMP_CACHE_BYTES - 1)) & \
				 ~(SMP_CACHE_BYTES - 1))

int main()
{
	int m = 1;
	m = SKB_DATA_ALIGN(m);
	printf("%d\n",m);
}
