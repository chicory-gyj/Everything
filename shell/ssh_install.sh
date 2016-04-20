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

#��������ļ�
if [ ! -f $SSH_FILE.tar.gz ]; then
  echo "source file $SSH_FILE.tar.gz doesn't exists! exit..."
  exit 1
fi

#����root��telnet�����ⲻ��ʹ��
mv /etc/securetty /etc/securetty.bak

#�����ļ��ı�SSH�����ȱʡbanner
sed -i 's/#Banner/Banner/g' /etc/ssh/sshd_config


#������Traceroute̽��  ���������
##/usr/local/sbin/iptables -A FORWARD -p icmp --icmp-type 11 -j DROP
##echo "/usr/local/sbin/iptables -A FORWARD -p icmp --icmp-type 11 -j DROP" >> /etc/ac_preload.sh

#ICMP timestamp������Ӧ©�� �������
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

#��֤ac���������������÷���
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
