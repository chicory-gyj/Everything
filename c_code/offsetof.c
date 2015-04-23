#define offsetof(TYPE, MEMBER) ((int) &((TYPE *)0)->MEMBER)

#define container_of(ptr, type, member) ((type *)( (char *)ptr - offsetof(type,member)))


struct value
{
	int a;
	int b;
	int c;	
};
int main()
{
	struct value test = { 5, 6, 7};
	printf("%d\n", offsetof(struct value, b));
	printf("b: %p\n",&test.b);
	
		

	printf("%p\n", (((char*)&test + 4)));
	return 0;
}
