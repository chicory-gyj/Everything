#!/usr/bin/perl
use strict;
use warnings;

my (@person);
sub greet 
{
    my ($this);
    $this = $_;
    if(@person == 0)
    {
        print "Hi",$this,"your are the first person!";
        push(@person,$this);
    }
    else
    {
        print "Hi",$this,"have been:",@person;
        push(@person,$this);
    }
}

greet("bb");
greet("add");
grert("cc");



