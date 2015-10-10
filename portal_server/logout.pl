#!/usr/bin/perl
print "Content-type: text/html\n\n";
#----------
chomp (my $para=<STDIN>);
my ($wlanacip, $wlanuserip, @array, $temp,$wlanacname,$version);

print "===== debug start =====<br>";
print "para:$para<br>";
@array = split(/&/,$para);
print "@array<br>";
foreach $temp (@array)
{
  if ($temp =~ /wlanacip/)
  {
      $temp  =~ s/wlanacip=//;
      $wlanacip = $temp;
  }
  elsif($temp =~ /wlanuserip/)
  {
      $temp =~ s/wlanuserip=//;
      $wlanuserip = $temp;
  }
  elsif($temp =~ /ver/)
  {
	$tmp =~ s/ver=//;
	$version = $temp;
  }
}
print "ACIP:$wlanacip,USERIP:$wlanuserip<br>";


my ( $sock, $port, $ipaddr, $iparray, @iparray,
     $MAXLEN, $PORTNO, $TIMEOUT, $serialno, $reqid, $req_logout, $ack_logout);

$MAXLEN  = 1024;
$PORTNO  = 2000;
$TIMEOUT = 2;

$reqid = 0;
$serialno = 0;

@iparray = split(/\./, $wlanuserip);

$req_logout = pack ("C C C C n n C4 n C C", 1, 5, 0, 0, $serialno, $reqid, @iparray, 0, 0, 0);
print "REQ_LOGOUT: ",unpack("H*",$req_logout),"<br>";

use IO::Socket;
$sock = IO::Socket::INET->new ( Proto     => 'udp',
                                PeerPort  => $PORTNO,
                                PeerAddr  => $wlanacip )
        or die {goto FAIL};
$sock->send ( $req_logout ) or die {goto FAIL};

eval
{
    local $SIG{ALRM} = sub { die {goto FAIL} };
    alarm $TIMEOUT;
    $sock->recv ( $ack_logout, $MAXLEN )      or die {goto FAIL};
    alarm 0;
    1;
# return value from eval on normalcy
} or die {goto FAIL};
print "ACK_LOGOUT: ",unpack("H*",$ack_logout),"<br>";
print "===== debug end =====","<br>";
print "<font color=\"#0000FF\">LOGOUT SUCCESS</font>","<br>";
die;

FAIL:
print "<font color=\"#FF0000\">LOGOUT FAIL!!!</font>","<br>";
