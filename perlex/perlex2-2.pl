#!/usr/bin/perl
use strict;
use warnings;

my ($pi, $radius, $out);
$pi = 3.1415;
print "please input radius\n";

$radius = <STDIN>;

$out = $radius * $pi;
print "the result is  $out\n";


