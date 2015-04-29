#!/usr/bin/env python
#coding=utf-8

import telnetlib

host = "192.168.1.102"
userName = 'root'
password = 'ieee802.11'
secret = 'ieee802.11'
enter = '\n'

t = telnetlib.Telnet(host)

t.read_until("login: ",1)
t.write(userName + enter)

t.read_until("Password: ",1)
t.write(password + enter)

t.read_until("mode: ",1)
t.write(secret + enter)

t.write("ls"+enter)
t.write("exit"+enter)

print t.read_all()
