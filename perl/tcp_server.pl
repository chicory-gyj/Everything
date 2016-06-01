#!/usr/bin/env perl

use IO::Socket;
$addr = "0.0.0.0";
$PORT = 9999;
$server = IO::Socket::INET->new(Proto => "tcp",
                                LocalPort => $PORT,
                                Listen => 20,
                                Reuse => 1) or
                            die "can't setup server";
print "accept clients\n";
#$msg = "HTTP/1.1 301 Moved Permanently\r\n";
$msg .= "HTTP/1.1 200 OK\r\n";
#$msg .=  "Location: http:10.50.123.52\r\n";
$msg .=  "Content-Type: text/html; charset=UTF-8\r\n",
#$msg .=  "Content-Type: text/javascript\r\n",
       $msg .=  "Cache-Control: no-cache\r\n",
       #$msg .=  "Server: gws\r\n",
       #$msg .=  "Content-Length:  900\r\n",
       $msg .=  "\r\n",
       $msg .= "<!DOCTYPE html>";
       $msg .=  "<HTML><HEAD><meta http-equiv=\"content-type\" content=\"text/html;charset=gb2312\">\n",
       #$msg .= "<HTML><HEAD><meta http-equiv=\"refresh\" content=\"1; url=http://10.50.123.52\">";
       $msg .=  "<TITLE>xxxsfafadsfxxxxxxx</TITLE>\n",
       #$msg .=  "The document has moved\n",
       #$msg .= "<p align=\"center\"><font color=\"#000000\" size=\"10\"></font> <a style=\"text-decoration: none\" href=\"http://10.50.123.52/\"><font color=\"#0066ff\" size=\"10\"></font></a>.</p>\n";
       $msg .= "<script type=\"text/javascript\">\n";
       #$msg .= "<script src=\"http://libs.baidu.com/jquery/1.9.1/jquery.min.js\"></script>\n";
       #$msg .= "<script language=\"javascript\" type=\"text/javascript\">\n";
       #$msg .= "\$(document).ready( function() { url = \"http://10.50.123.52?wlanuserip=172.168.1.101&wlanacname=11/11:ee.11.12&wlanacip=10.50.123.52&ssid=fang_haha&nasid=0000000000000460&usermac=34363b7fb17c&wlanapmac=0034cb00b1a7\"; \$( location ).attr(\"href\", url);     });";
       #$msg .= "delayURL(\"http://10.50.123.52:90\");\n";
       $msg .= "function gotourl(){window.top.location.href ='http://10.50.123.52:90?wlanuserip=172.168.1.101&wlanacname=11/11:ee.11.12&wlanacip=10.50.123.52&ssid=fang_haha&nasid=0000000000000460&usermac=34363b7fb17c&wlanapmac=0034cb00b1a7';} gotourl();\n";
       #$msg .= "function mytimer(){window.location.replace('http://10.50.123.52?wlanuserip=172.168.1.101&wlanacname=11/11:ee.11.12&wlanacip=10.50.123.52&ssid=fang_haha&nasid=0000000000000460&usermac=34363b7fb17c&wlanapmac=0034cb00b1a7')} mytimer();";
       #$msg .= "function redirect(){self.location.href = 'http://10.50.123.52:90?wlanuserip=172.168.1.101&wlanacname=11/11:ee.11.12&wlanacip=10.50.123.52&ssid=fang_haha&nasid=0000000000000460&usermac=34363b7fb17c&wlanapmac=0034cb00b1a7';}redirect();";
       $msg .= "</script>\n";
       #$msg .=  "<A HREF=\"http://www.google.com/\">here</A>.\r\n",
       $msg .=  "</HEAD><BODY>hahahahahah</BODY></HTML>\r\n";
while ($client = $server->accept())
{
    print "haha\n";
    $client->recv($hhhh,1000);
    $client->send($msg);
    # close($client);
}
