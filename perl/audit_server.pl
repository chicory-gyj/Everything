#!/usr/bin/env perl

use IO::Socket;
$addr = "0.0.0.0";
$PORT = 9876;
$server = IO::Socket::INET->new(Proto => "tcp",
                                LocalPort => $PORT,
                                Listen => 20,
                                Reuse => 1) or
                            die "can't setup server";
print "accept clients\n";

while ($client = $server->accept())
{
    print "start\n";
    while(1)
    {
        $client->recv($msg,15000);
        $total_len = length $msg;
        print "\nrecv length: ", $total_len,"";
        print "\nrecv: ", unpack("H*", $msg);
        $count = 0;
        $pos = 0;
        $msg_portion_len = 0;
        while($total_len > 0)
        {
            $count ++;
            $msg_portion_len = unpack("x$pos C", $msg)*256 + unpack("x1 x$pos C", $msg);
            $serial_num_postion = $pos + 8;
            $msg_serial = unpack("x$serial_num_postion C", $msg)*256 + unpack("x1 x$serial_num_postion C", $msg);
            $tcpheadlen_postion = $pos + 56;
            $msg_tcpheadlen = unpack("x$tcpheadlen_postion H2", $msg);
            $iplen_postion = $pos + 26;
            $msg_iplen = unpack("x$iplen_postion C", $msg)*256 + unpack("x1 x$iplen_postion C", $msg);
            print "\nmsg",$count," length: ", $msg_portion_len, " serial: ", $msg_serial, " tcp headlen: ", $msg_tcpheadlen, " iplen: ", $msg_iplen;
            if(($msg_iplen +24) != $msg_portion_len)
            {
                print "\n ERR!!!";
            }

            $len = 2*$msg_portion_len;
            print "\nmsg", $count, ": ", unpack("x$pos H$len", $msg);

            $pos += $msg_portion_len;
            $total_len -= $msg_portion_len;
        }
        print "\n";
    }
}
