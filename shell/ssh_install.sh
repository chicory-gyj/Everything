#!/bin/sh
#set -x

CUR_PATH=`pwd`
SSH_FILE="appfs"


echo "Do you want to continue the openssh and openssl package install?  "
echo -n "[Y/n (Default no)]:"
read continue_as_version_err
if [ "$continue_as_version_err" != "Y" ]; then
  exit 1
fi

#检查配置文件
if [ ! -f $SSH_FILE.tar.gz ]; then
  echo "source file $SSH_FILE.tar.gz doesn't exists! exit..."
  exit 1
fi

#开启root的telnet，以免不能使用
mv /etc/securetty /etc/securetty.bak

#配置文件改变SSH服务的缺省banner
sed -i 's/#Banner/Banner/g' /etc/ssh/sshd_config


#不允许Traceroute探测  解决方案：
##/usr/local/sbin/iptables -A FORWARD -p icmp --icmp-type 11 -j DROP
##echo "/usr/local/sbin/iptables -A FORWARD -p icmp --icmp-type 11 -j DROP" >> /etc/ac_preload.sh

#ICMP timestamp请求响应漏洞 解决方案
#/usr/local/sbin/iptables -A INPUT -p icmp --icmp-type timestamp-request -j DROP
#/usr/local/sbin/iptables -A OUTPUT -p icmp --icmp-type timestamp-reply -j DROP
##/usr/local/sbin/iptables -A INPUT -p icmp --icmp-type 13 -j DROP
##/usr/local/sbin/iptables -A OUTPUT -p icmp --icmp-type 14 -j DROP
##echo "/usr/local/sbin/iptables -A INPUT -p icmp --icmp-type 13 -j DROP" >> /etc/ac_preload.sh
##echo "/usr/local/sbin/iptables -A OUTPUT -p icmp --icmp-type 14 -j DROP" >> /etc/ac_preload.sh

cd $CUR_PATH
rm -rf /$SSH_FILE
tar zxvf $SSH_FILE.tar.gz
mv $SSH_FILE /

service sshd stop

sed -i 's/#Banner/Banner/g' /appfs/etc/sshd_config

#保证ac重启后正常启动该服务
echo "/appfs/sbin/sshd" >> /etc/rc.local

chkconfig sshd --list
chkconfig sshd off

/appfs/sbin/sshd


echo "----------------------------------------result-----------------------------------------------------------"
echo "install $SSH_FILE.tar.gz success!!!"
echo "check openssh version..."
/appfs/bin/ssh -V
cat /appfs/etc/sshd_config | grep Banner
chkconfig sshd --list
echo "---------------------------------------------------------------------------------------------------------"

netstat -tnlp | grep :22 

ps -aux | grep ssh
