/*
 * =====================================================================================
 *
 *       Filename:  sprintf.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  03/10/2016 08:06:33 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */
#include <stdlib.h>
int main()
{
    /* int port = 0; */
    /* char string[128] = {0}; */
    /* int plus = 0; */
    /* plus += sprintf(&string[plus], port?" \ */
    /*         1 %d": \ */
    /*         "", port?port:0); */
    /* printf("plus: %d\n", plus); */
    /* printf("string: %s\n", string); */

    /* char str[32] = {0}; */
    /* sprintf(str, "%d", 1000); */
    /* printf("str: %s\n", str); */

    char test[100] = {0};
    sprintf(test, "%s", "abc");
    printf("test: %s", test);
    sprintf(test, "%s", "ft");
    printf("\ntest: %s", test);
}

