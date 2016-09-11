#!/usr/bin/env python
import urllib2
import csv
import time
import socket

hdr = {'User-Agent': 'Mozilla/5.0 (X11; Linux x86_64) AppleWebKit/537.11 (KHTML, like Gecko) Chrome/23.0.1271.64 Safari/537.11',
       'Accept': 'text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8',
       'Accept-Charset': 'ISO-8859-1,utf-8;q=0.7,*;q=0.3',
       'Accept-Encoding': 'none',
       'Accept-Language': 'en-US,en;q=0.8',
       'Connection': 'keep-alive'}

market = 'SH'
code = '603980'
local_timeout = 3
url = 'http://xueqiu.com/S/' + market + str(code) + '/historical.csv'
req = urllib2.Request(url, headers = hdr)
content = urllib2.urlopen(req, timeout = local_timeout).read()

print content
