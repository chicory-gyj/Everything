#!/usr/bin/perl
use strict;
use warnings;

my(@line, $FILE, $tempfile);
while(@ARGV)
{
	$tempfile = shift(@ARGV);
	open FILE, $tempfile;
	@line = reverse <FILE>;
	print @line; 
}
