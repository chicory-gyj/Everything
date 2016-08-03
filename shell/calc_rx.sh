#!/bin/bash

device=$1

if [ "$device" ];then
	echo calculating $device rate ...
	echo you can use this to see: tail -f $device
else
	echo "Please input device!"
	exit 1
fi

intervalo=1
info="/sys/class/net/"
cd $info
while [[ 1 > 0 ]]
do
    for interface in $device
    do
        rx1=`cat $info$interface/statistics/rx_bytes`
        tx1=`cat $info$interface/statistics/tx_bytes`
        `sleep $((intervalo))s`
        rx2=`cat $info$interface/statistics/rx_bytes`
        tx2=`cat $info$interface/statistics/tx_bytes`
        echo $interface >> ~/$interface
        echo ---- >> ~/$interface
        echo RX: $((($rx2-$rx1)/($intervalo*1024))) Kbps >> ~/$interface
        echo RX: $((($rx2-$rx1)/($intervalo*1024*1024))) Mbps >> ~/$interface
        echo TX: $((($tx2-$tx1)/($intervalo*1024))) Kbps >> ~/$interface
        echo TX: $((($tx2-$tx1)/($intervalo*1024*1024))) Mbps >> ~/$interface
	echo `date` >> ~/$interface
    done
done
