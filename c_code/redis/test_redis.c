#include "hiredis.h"
int main()
{
    redisReply *reply;
    redisContext* c = redisConnect((char*)"127.0.0.1", 7000);
    if (c->err)
    {
        printf("wrong\n");
        redisFree(c);
        return;
    }
    reply = redisCommand(c, "PING");
    printf("PING: %s\n", reply->str);
    freeReplyObject(reply);

    reply = redisCommand(c, "set fangzheng good");
    printf("value: %s\n", reply->str);
    freeReplyObject(reply);

    reply = redisCommand(c, "get fangzheng");
    printf("value: %s\n", reply->str);
    freeReplyObject(reply);
}
