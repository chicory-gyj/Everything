#include <stdio.h>
int main()
{
				char pbyBody[100]="aaabbb";
				int wLen = 10;
				FILE *fp;
				int i;
			        if ((fp = fopen("/home/hostapd_cpu.log", "a+")) == NULL)
			        {
			                system("echo Fail >> /home/hostapd_cpu.log");
			        }
 					char *pp;
					pp = pbyBody;
			        for(i = 0;i < wLen; i++)
			        {
			                fprintf(fp, "%02X ", *(pp+i) );
			        }
			        fprintf(fp,"\n");
				fclose(fp);
}
