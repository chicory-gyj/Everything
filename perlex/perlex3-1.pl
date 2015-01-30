#!/usr/bin/perl
use strict;
use warnings;

print "please input string and press Ctrl+D end ...\n";

my (@line );
@line = <stdin>;

print reverse @line;



