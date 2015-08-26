#!/usr/bin/perl

use Encode qw(decode encode);

$octets = "http://2@163&13";
$characters =  encode('utf8', $octets);
print $characters;
$octets     = decode('UTF-8', $characters, Encode::FB_CROAK);
print $octets;
