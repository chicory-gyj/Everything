#!/usr/bin/perl
use strict;
use warnings;

my ($arg, $temp, @split);
foreach $arg (@ARGV)
{
    @split = split /\./, $arg;
    $temp = $split[0]."\.html";
    print $temp,"\n";
    system "pandoc $arg -s -o $temp";
}
