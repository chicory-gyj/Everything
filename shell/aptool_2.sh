#!/bin/bash
echo "please input ip:"

i=1
read ip

while (($i<2))
do
    sleep 1;
    ((sleep 1;echo "root";
    sleep 1; echo "ieee802.11";
    sleep 1; echo "ieee802.11";
    sleep 1; echo "free";sleep 2
    )|telnet $ip)
done

