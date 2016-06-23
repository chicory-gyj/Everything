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

while ($client = $server->accept())
{
    print "start\n";
    while(1)
    {
        sleep 1;
        $client->recv($msg,15000);
        $total_len = length $msg;
        print "\nrecv length: ", $total_len,"";
        print "\nrecv: ", unpack("H*", $msg);
        if($total_len == 0)
        {
            break;
        }
        $client->send("hahahah");

        print "\n";
    }
}
