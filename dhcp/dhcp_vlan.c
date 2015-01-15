#include<stdlib.h>
#include<stdio.h>    
#include<string.h>

#define VLANINFO "/tmp/vlaninfo"                   
#define MAXLINE 1024                               

char g_line[32][MAXLINE] = {0};                    

int get_vlaninfo()                                 
{                                                  
    FILE *fp;                                      
    if((fp = fopen(VLANINFO,"r")) == NULL)
    {                                              
        return 1;                                  
    }                                              
    int i = 0;                                     
    while((fgets(g_line[i], MAXLINE, fp) != NULL)) 
    {                                              
        if(i > 31)                                 
        {                                          
            return 1;                              
        }                                          
        i++;                                       
    }                                              
    return 0;                                      
}                                                  
int analysis_vlan(int vlanin,int *vlanout)        
{                                                  
    int i = 0;   
    char vlantmp[16] = "VLAN";
    snprintf(vlantmp,8,"%d",vlanin);
    char acvlanin[16] = "VLAN";                             
    char acvlanout[16];                            
    char *pcolon;                                   
    strcat(acvlanin,vlantmp);                
    strcat(acvlanin,":");                          
    for(i = 0; i < 32; i ++)                            
    {                                              
        if(strstr(g_line[i], acvlanin))             
        {    
            char tmp[MAXLINE];
            strncpy(tmp, g_line[i], MAXLINE);
            if((pcolon = strstr(tmp, "=")) != NULL)          
            {
                *pcolon = '\0';
                *vlanout = atoi(tmp+4);
                return 0;
            }
            else
            {
                return 1;
            }
        }                                          

    }                                              
}                                                  
int main()
{
    get_vlaninfo();
    int a = 99;
    int b;
    analysis_vlan(a,&b);
    printf("%d\n",b);

    analysis_vlan(87,&b);
    printf("%d\n",b);
    analysis_vlan(2,&b);
    printf("%d\n",b);
}
