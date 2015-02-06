#!/usr/bin/perl
use strict;
use warnings;

my ($arg, $temp, @split);
foreach $arg (@ARGV)
{
    @split = split /\./, $arg;
    $temp = $split[0];
    print $temp,"\n";
    system "pandoc $arg -t html -s -o $temp";
}
