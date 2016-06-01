int main()
{
    unsigned char test[2] ={0};
    memcpy(test, int*(0x1122), 2);

    printf("%d %d\n", test[0], test[1]);
}
