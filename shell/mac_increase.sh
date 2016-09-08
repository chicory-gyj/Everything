#!/bin/bash
mac=$(ifconfig enp3s10|grep HWaddr|awk '{print $5}'| tr '[a-z]' '[A-Z]' | cut -d ':' -f1-5)
maclast=$(ifconfig enp3s10|grep HWaddr|awk '{print $5}'| tr '[a-z]' '[A-Z]' | cut -d ':' -f6)
echo "Mac address= $mac:$maclast"
decmac=$(echo "ibase=16; $maclast"|bc)
if [ $decmac -eq '241' ]
then
macinc='00'
else
incout=`expr $decmac + 1 `
macinc=$(echo "obase=16; $incout"|bc)
fi
echo "Mac address= $mac:$macinc"
