nclude<stdio.h>                                  
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
                                                printf("%d:%s\n", i,g_line[i]);            
                                                        i++;                                       
                                                            }                                              
                        return 0;                                      
}                                                  
int analysis_vlan(int *vlanin,int *vlanout)        
{                                                  
        int i=0;                                       
            char acvlanin[16];                             
                char acvlanout[16];                            
                    char pcolon;                                   
                        strcat(acvlanin,itoa(*vlanin));                
                            strcat(acvlanin,'.');                          
                                printf("vlanin:%s\n",acvlanin);                
                                    for(i=0; i++; i<32)                            
                                            {                                              
                                                        if(strstr(acvlanin,g_line[i]))             
                                                                    {                                          
                                                                                    if(p = strstr(':',g_line[i]))          
                                                                                                    {                                      
                                                                                                                                                           
                                                                                                                    }                                      
                                                                                            }                                          
                                                                                                           
                                                            }                                              
}                                                  

