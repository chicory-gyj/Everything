#!/usr/bin/env python

import urllib2
import csv
import time
import socket
import ssl

hdr = {'User-Agent': 'Mozilla/5.0 (X11; Linux x86_64) AppleWebKit/537.11 (KHTML, like Gecko) Chrome/23.0.1271.64 Safari/537.11',
       'Accept': 'text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8',
       'Accept-Charset': 'ISO-8859-1,utf-8;q=0.7,*;q=0.3',
       'Accept-Encoding': 'none',
       'Accept-Language': 'en-US,en;q=0.8',
       'Connection': 'keep-alive'}

markets = 'SH SZ'
market = 'SH'
if market == 'SH':
    code_start = '600000'
    code_end   = '604000'
elif market == 'SZ':
    code_start = '000001'
    code_end   = '003000'

date_need = "2015-01-01"
local_timeout = 3

myfile = open(market + "_history", 'a+')
myfile.write(time.strftime("%d/%m/%Y") + '\n')
myfile.close()

for code in range(int(code_start), int(code_end)):
    #code = '002481'
    content_date_ok = []
    weight = 1
    code = str(code).zfill(6)
    url = 'http://xueqiu.com/S/' + market + str(code) + '/historical.csv'
    req = urllib2.Request(url, headers = hdr)
    try:
        content = urllib2.urlopen(req, timeout = local_timeout).read()
    except urllib2.HTTPError, e:
        continue
    except urllib2.URLError, e:
        continue
    except socket.timeout, e:
        continue
    except ssl.SSLError, e:
        continue
    if str(code) not in content:
        continue
    content = content.replace('"', '')
    content_delete_first_line = '\n'.join(content.split('\n')[1:])
    content_rstrip = content_delete_first_line.rstrip('\n')
    print "result:"
    #print content_rstrip
    content_list = content_rstrip.split('\n')
    content_list_in_list = [x.split(',') for x in content_list]
    for x in content_list_in_list:
        if x[1] > date_need:
            content_date_ok.append(x)
    content_list_in_list = content_date_ok
    if not content_list_in_list:
        continue
    for idx, x in enumerate(content_list_in_list):
        if (idx + 1) == len(content_list_in_list):
            break
        idy = idx
        y = content_list_in_list[(idy + 1) % len(content_list_in_list)]
        while float(y[2]) == 0:
            idy = idy + 1
            if idy == len(content_list_in_list):
                break
            y = content_list_in_list[(idy + 1) % len(content_list_in_list)]
        if float(y[2]) == 0:
            continue
        delta = float(x[5])/float(y[2])
        print "delta:" + str(delta)
        if delta > 1.15:
            weight = weight * delta
            print "Date " + y[1] + " Weight:" + str(weight)
    current_price = float(content_list_in_list[-1][5])
    sorted_by_second = sorted(content_list_in_list, key=lambda x: float(x[5]), reverse=True)
    biggest_price = float(sorted_by_second[0][5])
    if current_price == 0.0:
        continue
    weight = round(weight, 2)
    star = biggest_price/current_price
    star = star/weight
    star = round(star, 2)
    print 'Current Price: ' + str(current_price)
    print 'Biggest Price: ' + str(biggest_price)
    print 'Weight:' + str(weight)
    print 'Star ' + str(code) + ': ' + str(star) + '\n'
    out = 'Current Price: ' + str(current_price) + '\n'
    out = out + 'Biggest Price: ' + str(biggest_price) + '\n'
    out = out + 'Weight:' + str(weight) + '\n'
    out = out + 'Star ' + str(code) + ': ' + str(star) + '\n'
    myfile = open(market + "_history", 'a+')
    myfile.write(out)
    myfile.close()
