struct stu
{
    int aa;
    int bb;
    int cc;
    int dd;
}
int main()
{
    struct stu mimi;
    mimi.aa = 1;
    mimi.bb = 100;
    mimi.cc = 54;
    mimi.dd = 99;

    struct stu *bb;
    bb = (struct stu *)&mimi;
    printf("aa:%\n"
            "bb:%d\n"
            "cc:%d\n"
            "dd:%d\n",
            bb.aa,
            bb.bb,
            bb.cc,
            bb.dd);
}
