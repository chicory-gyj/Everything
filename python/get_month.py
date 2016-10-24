#!/usr/bin/env python

import urllib2
import time
import socket
import ssl
import time
from datetime import date

hdr = {'User-Agent': 'Mozilla/5.0 (X11; Linux x86_64) AppleWebKit/537.11 (KHTML, like Gecko) Chrome/23.0.1271.64 Safari/537.11',
       'Accept': 'text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8',
       'Accept-Charset': 'ISO-8859-1,utf-8;q=0.7,*;q=0.3',
       'Accept-Encoding': 'none',
       'Accept-Language': 'en-US,en;q=0.8',
       'Connection': 'keep-alive'}

date_need = "2014-01-01"
content_date_ok = []

jan_sum = 0
feb_sum = 0
mar_sum = 0
apr_sum = 0
may_sum = 0
jun_sum = 0
jul_sum = 0
aug_sum = 0
sep_sum = 0
oct_sum = 0
nov_sum = 0
dec_sum = 0

market = 'SH'
code = '000001'
local_timeout = 3
url = 'http://xueqiu.com/S/' + market + str(code) + '/historical.csv'
req = urllib2.Request(url, headers = hdr)
content = urllib2.urlopen(req, timeout = local_timeout).read()
content = content.replace('"', '')
content_delete_first_line = '\n'.join(content.split('\n')[1:])
content_rstrip = content_delete_first_line.rstrip('\n')
print "result:"
#print content
content_list = content_rstrip.split('\n')
content_list_in_list = [x.split(',') for x in content_list]
for x in content_list_in_list:
    if x[1] > date_need:
        content_date_ok.append(x)
content_list_in_list = content_date_ok

if not content_list_in_list:
    exit
#print content_list_in_list


for idx, x in enumerate(content_list_in_list):
    if (idx + 1) == len(content_list_in_list):
        break
    print x
    year, month, day = x[1].split("-")
    need_year, need_month, need_day = date_need.split("-")
    if (year != need_year):
        continue
    if (int(month) == 1):
       jan_sum += (float(x[5]) - float(x[2]))/float(x[2])
       print '1 month'
       print jan_sum
    if (int(month) == 2):
       feb_sum += (float(x[5]) - float(x[2]))/float(x[2])
       print '2 month'
       print feb_sum
    if (int(month) == 3):
       mar_sum += (float(x[5]) - float(x[2]))/float(x[2])
       print '3 month'
       print mar_sum
    if (int(month) == 4):
       apr_sum += (float(x[5]) - float(x[2]))/float(x[2])
       print '4 month'
       print apr_sum
    if (int(month) == 5):
       may_sum += (float(x[5]) - float(x[2]))/float(x[2])
       print '5 month'
       print may_sum
    if (int(month) == 6):
       jun_sum += (float(x[5]) - float(x[2]))/float(x[2])
       print '6 month'
       print jun_sum
    if (int(month) == 7):
       jul_sum += (float(x[5]) - float(x[2]))/float(x[2])
       print '7 month'
       print jul_sum
    if (int(month) == 8):
       aug_sum += (float(x[5]) - float(x[2]))/float(x[2])
       print '8 month'
       print aug_sum
    if (int(month) == 9):
       sep_sum += (float(x[5]) - float(x[2]))/float(x[2])
       print '9 month'
       print sep_sum
    if (int(month) == 10):
       oct_sum += (float(x[5]) - float(x[2]))/float(x[2])
       print '10 month'
       print oct_sum
    if (int(month) == 11):
       nov_sum += (float(x[5]) - float(x[2]))/float(x[2])
       print '11 month'
       print nov_sum
    if (int(month) == 12):
       dec_sum += (float(x[5]) - float(x[2]))/float(x[2])
       print '12 month'
       print dec_sum

print '------------'
print '1 month'
print jan_sum
print '2 month'
print feb_sum
print '3 month'
print mar_sum
print '4 month'
print apr_sum
print '5 month'
print may_sum
print '6 month'
print jun_sum
print '7 month'
print jul_sum
print '8 month'
print aug_sum
print '9 month'
print sep_sum
print '10 month'
print oct_sum
print '11 month'
print nov_sum
print '12 month'
print dec_sum
