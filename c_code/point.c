int g_i = 100; 
int *g_p;
void func(int **pa)
{
	*pa = &g_i;
	printf("%d\n", **pa);
}

int main()
{
	int **pa;
	func(pa);
	printf("%d\n",**pa);
}
