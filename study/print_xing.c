int main()
{
	int n = 10;
	int i = 0;
	int j = 0;
	for (i = 0;i < n;i ++)
	{
		for(j = 0;  j<=(n*2 - 1); j++)
		{
			if(j>(i + n)||(j<n-i))
			{
				printf(" ");
			}
			else
			{
				printf("*");
			}
		}
		printf("\n");
	}
}
