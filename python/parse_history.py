import urllib2
import csv

hdr = {'User-Agent': 'Mozilla/5.0 (X11; Linux x86_64) AppleWebKit/537.11 (KHTML, like Gecko) Chrome/23.0.1271.64 Safari/537.11',
       'Accept': 'text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8',
       'Accept-Charset': 'ISO-8859-1,utf-8;q=0.7,*;q=0.3',
       'Accept-Encoding': 'none',
       'Accept-Language': 'en-US,en;q=0.8',
       'Connection': 'keep-alive'}

market     = 'SH'
code_start = 600000
code_end   = 604000

code = 600770
for code in range(code_start, code_end):
    url = 'http://xueqiu.com/S/' + market + str(code) + '/historical.csv'
    req = urllib2.Request(url, headers = hdr)
    content = urllib2.urlopen(req, timeout = 3).read()
    if str(code) not in content:
        continue
    content = content.replace('"', '')
    content_delete_first_line = '\n'.join(content.split('\n')[2:])
    content_rstrip = content_delete_first_line.rstrip('\n')
    content_list = content_rstrip.split('\n')
    content_list_in_list = [x.split(',') for x in content_list]
    current_price = float(content_list_in_list[-1][5])
    print 'Current Price: ' + str(current_price)
    sorted_by_second = sorted(content_list_in_list, key=lambda x: float(x[5]), reverse=True)
    biggest_price = float(sorted_by_second[0][5])
    print 'Biggest Price: ' + str(biggest_price)
    star = biggest_price/current_price
    star = round(star, 2)
    print 'Star ' + str(code) + ' : ' + str(star) + '\n'
