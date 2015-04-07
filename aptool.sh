#!/bin/bash
echo "please input ip:";
read ip;
((sleep 1;echo "root";
sleep 1; echo "ieee802.11";
sleep 1; echo "ieee802.11";
sleep 1; echo "logctl -l on;tail -f  /var/log/messages"; 
sleep 2000000; 
)|telnet $ip);

