int main()
{
    int a = 51235;
    int b = 78902;
    int c = a^b;
    printf("%d\n", c);
    a = a^c;
    printf("%d\n",a);
    b = b^c;
    printf("%d\n",b);
}
