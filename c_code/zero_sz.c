struct pack
{
    unsigned char a[4];
    unsigned char b[4];
    int c[0];
}

int main()
{
    unsigned char test[100] = "hello world 999";
    printf("%s\n", ((struct pack *)test)->a);
    
}
