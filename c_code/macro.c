
#define AUDIT_VID_DPI_WECHAT                 1030036    /* 微信 */
#define AUDIT_VID_DPI_QQ                     1030001    /* 腾讯QQ */
#define AUDIT_APP_WECHAT     1    /* 微信 */
#define AUDIT_APP_QQ            2   /* QQ */

int trans(int type)
{
#define AUDIT_VID_DPI_TRANS_CODE(_var)\
    case AUDIT_APP_##_var: return AUDIT_VID_DPI_##_var;

    switch(type)
    {
        AUDIT_VID_DPI_TRANS_CODE(QQ);
    }
}

int main()
{

}
