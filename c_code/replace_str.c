/*
 * substring to be replace
 */
void replace_str(char *str, char *sub, char *rep)
{
    char *p;

    if(!(p = strstr(str, sub)))
        return;

    sprintf(str + (p - str), "%s%s", rep, p + strlen(sub));
    return;
}

