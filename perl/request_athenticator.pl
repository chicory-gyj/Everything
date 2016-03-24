#!/usr/bin/env perl
use Digest::MD5 qw(md5 md5_hex md5_base64);

$msg = 
$password="cmedia";

print "\n";
print unpack("H*", $password);

$authenticator = md5($msg, $password);

print "\n";
print unpack("H*", $authenticator);
