int main()
{
    char *p = malloc(10);
    sprintf(p, "%s", "hhhhhhhhh");
    printf("size:%d\n", sizeof(p));

    char *q = realloc(p, 20);
    printf("size:%d\n", sizeof(q));
}
