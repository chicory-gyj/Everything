#!/bin/bash
STATUS=`ps aux|grep ssh|grep NfR`

echo ${STATUS}

if [ ! "${STATUS}" ];then
    ssh -NfR 0.0.0.0:9990:localhost:22 fabius8@54.199.171.197 -o GatewayPorts=yes -o ConnectTimeout=10 -o ConnectionAttempts=5 -o ServerAliveInterval=2
fi

