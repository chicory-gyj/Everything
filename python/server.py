#!/usr/bin/env python

import socket

serversocket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
serversocket.bind(('localhost', 50100))

while True:
    buf = serversocket.recv(512)
    if len(buf) > 0:
        print buf,len(buf)
        break
