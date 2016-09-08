import urllib2
import csv

hdr = {'User-Agent': 'Mozilla/5.0 (X11; Linux x86_64) AppleWebKit/537.11 (KHTML, like Gecko) Chrome/23.0.1271.64 Safari/537.11',
       'Accept': 'text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8',
       'Accept-Charset': 'ISO-8859-1,utf-8;q=0.7,*;q=0.3',
       'Accept-Encoding': 'none',
       'Accept-Language': 'en-US,en;q=0.8',
       'Connection': 'keep-alive'}

markets = 'SH SZ'
market = 'SZ'
if market == 'SH':
    code_start = '600000'
    code_end   = '604000'
elif market == 'SZ':
    code_start = '000001'
    code_end   = '004000'

date_need = "2015-01-01"

for code in range(int(code_start), int(code_end)):
    content_date_ok = []
    code = str(code).zfill(6)
    url = 'http://xueqiu.com/S/' + market + str(code) + '/historical.csv'
    req = urllib2.Request(url, headers = hdr)
    content = urllib2.urlopen(req, timeout = 10).read()
    if str(code) not in content:
        continue
    content = content.replace('"', '')
    content_delete_first_line = '\n'.join(content.split('\n')[2:])
    content_rstrip = content_delete_first_line.rstrip('\n')
    content_list = content_rstrip.split('\n')
    content_list_in_list = [x.split(',') for x in content_list]
    for x in content_list_in_list:
        if x[1] > date_need:
            content_date_ok.append(x)
    content_list_in_list = content_date_ok
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
