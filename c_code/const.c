/*
 * =====================================================================================
 *
 *       Filename:  const.c
 *
 *    Description: 
 *
 *        Version:  1.0
 *        Created:  12/04/2015 10:03:14 AM
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
    char *buf = "haha";
    char *hah = "111";
    const char *http = buf;
    printf("%s\n", http);
    http = hah;
    printf("%s\n", http);
}
