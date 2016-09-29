#include "hircluster.h"
int main()
{
    redisReply *reply;
    redisClusterContext* c = redisClusterConnect((char*)"127.0.0.1:7000",
                                                 HIRCLUSTER_FLAG_NULL);
    if (c->err) {
        printf("wrong\n");
        redisFree(c);
        return;
    }
    /* reply = redisClusterCommand(c, "PING"); */
    /* printf("PING: %s\n", reply->str); */
    /* freeReplyObject(reply); */

    for (int i; i <= 50000; i++) {
        #if 1
        reply = redisClusterCommand(c, "set h{36}%d %d", i, i);
        printf("set %d %s\n", i, reply->str);
        freeReplyObject(reply);
        #else
        reply = redisClusterCommand(c, "get test%d", i);
        //redisClusterGetReply(c, &reply);
        printf("get: %s\n", reply->str);
        freeReplyObject(reply);
        #endif
    }
}
