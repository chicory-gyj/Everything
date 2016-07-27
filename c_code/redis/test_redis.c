#include"hiredis.h"
int main()
{
     redisContext* c = redisConnect((char*)"127.0.0.1", 6379);  
     if (c->err) 
     {
	printf("wrong\n");  
         redisFree(c);  
         return;  
     }
	printf("OK\n");
}
