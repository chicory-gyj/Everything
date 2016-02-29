#!/bin/env perl

$org_file = "../../fabius8.github.io/stock/stock.org";
open file, "<", $org_file;

while(<file>)
{
    chomp;
    print $_;
}


close file;
