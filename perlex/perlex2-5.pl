#!/usr/bin/perl
use strict;
use warnings;

my($string,$num);
print "please input string\n";
$string = <STDIN>;

print "please input number repeat the string\n";
$num = <STDIN>;
chomp($string);
while($num > 0)
{
    print "$string\n";
    $num--;
}


