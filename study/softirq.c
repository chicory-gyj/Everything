int main()
{
	unsigned int uia = 100;
	do
	{
		if(uia & 1)
		{
			printf("HAHA\n");
		}
		uia >>= 1 ;
	}while(uia);
}
