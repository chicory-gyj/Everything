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
    content_date_ok = []
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
    if str(code) not in content:
        continue
    content = content.replace('"', '')
    content_delete_first_line = '\n'.join(content.split('\n')[1:])
    content_rstrip = content_delete_first_line.rstrip('\n')
    content_list = content_rstrip.split('\n')
    content_list_in_list = [x.split(',') for x in content_list]
    for x in content_list_in_list:
        if x[1] > date_need:
            content_date_ok.append(x)
    content_list_in_list = content_date_ok
    if not content_list_in_list:
        continue
    current_price = float(content_list_in_list[-1][5])
    sorted_by_second = sorted(content_list_in_list, key=lambda x: float(x[5]), reverse=True)
    biggest_price = float(sorted_by_second[0][5])
    if current_price == 0.0:
        continue
    star = biggest_price/current_price
    star = round(star, 2)
    print 'Current Price: ' + str(current_price)
    print 'Biggest Price: ' + str(biggest_price)
    print 'Star ' + str(code) + ': ' + str(star) + '\n'
    out = 'Star ' + str(code) + ': ' + str(star) + '\n'
    myfile = open(market + "_history", 'a+')
    myfile.write(out)
    myfile.close()
