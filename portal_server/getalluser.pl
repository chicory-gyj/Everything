#!/usr/bin/perl
use IO::Socket;
my ($acip, $port, $smsg, $sock);
$acip = '127.0.0.1';
$port = '2000';
$sock = IO::Socket::INET->new ( 
    Proto     => 'udp',
    PeerPort  => $port,
    PeerAddr  => $acip )
    or die "new sock fail!\n";
$smsg = pack ("I C C C", 888, 1, 1, 1);
$sock->send ( $smsg) or die "send msg!\n";

