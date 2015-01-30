#!/usr/bin/perl
use strict;
use warnings;

sub total 
{
    my($max, $i);
    foreach(@_)
    {
        $max += $_;
        $i++;
    }   
    print "max:$max\n";
    return $max;
};

&total(1..1000);




