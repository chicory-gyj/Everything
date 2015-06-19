/*
 * =====================================================================================
 *
 *       Filename:  ctime.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2015年06月11日 17时56分39秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */
#include <stdlib.h>
int main(){
time_t result = time(NULL); 
char str[26];               
strcpy(str, ctime(&result));
printf("%s\n",str);
}

