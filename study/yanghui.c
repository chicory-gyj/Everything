int main()
{
	int n = 10;
	int i,j;
	int a[10][19]={0};
	a[0][9] = 1;
	for (i = 0; i < 10; i++)
	{
		for (j = 0; j < n*2-1; j++)
		{
			if(i == 0)
			{
				goto SKIP;
			}
			if( j<1)
			{
				a[i][j] = a[i-1][j+1];
			}
			else if( j+1 == n*2-1)
			{
				a[i][j] = a[i-1][j-1];
			}
			else
			{
				a[i][j] = a[i-1][j-1]+a[i-1][j+1];
			}
SKIP:
			if(a[i][j] ==0)
			{
				printf("    ");
			}
			else
			{
				printf("%4d",a[i][j]);
			}
		}
		printf("\n\n");
	}
}
