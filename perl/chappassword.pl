#!/usr/bin/env perl
use Digest::MD5 qw(md5 md5_hex md5_base64);

$reqid = 5;
$password = 1;
@challenge = (0x4e,0x6e,0x24,0xd5);
print "\n";
$cha = pack("C*", @challenge);

print "\n";
print unpack("H*",$cha);

print "\n";
$chappassword = md5($reqid,$password,$challenge);

print unpack("H*", $chappassword);

