#!/usr/bin/env perl
use Proc::Daemon;
use IO::Socket;
#$daemon = Proc::Daemon->new(
#    work_dir     => './',
#    pid_file     => 'pid.txt',
#);
#$Kid_1_PID = $daemon->Init;
#open LOG, ">>./haha.log";
$sock = IO::Socket::INET->new ( 
    Proto     => 'udp',
    LocalAddr => '10.60.123.222',
    LocalPort  => '50100',
    Timeout => '5')
    or die { print LOG "dir\n"};


while (1) 
{
    print "111";
    $sock->recv($msg,1000);
    print "$msg";
}
