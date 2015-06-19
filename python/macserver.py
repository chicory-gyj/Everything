#!/usr/bin/env python
import daemon
import time
f = open("workfile","a")
with daemon.DaemonContext():
    while True:
        f.write("aaa")
        sleep (1)
