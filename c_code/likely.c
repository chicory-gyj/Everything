#define likely(x)	__builtin_expect(!!(x), 1)

void test1()
{
	int a = 0;
	if (a == 0)
	{
		a=1;
	}
	else
	{
		a=2;
	}
}
void test2()
{
	int a =0;
        if (likely(a == 0))
        {
                a=1;
        }
        else
        {
                a=2;
        }

}

int main(){}
