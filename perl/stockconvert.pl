#!/bin/env perl
$filename = "/samba/sh000001.org";
open file ,"<","$filename";

$stockfile = '/home/fabius8/github/fabius8.github.io/stock/stock.org';
open sfile ,">>$stockfile";

while(<file>)
{
    if($_ =~ s/\* //)
    {
        chomp;
        $date = $_;
        print $_;
        print sfile "| ", $_, " | ";
    }
    else
    {
        chomp;
        $_ =~ /09:29 (\d+)亿 ((-?)(\d+).(\d+)) .* 11:30 (\d+)亿 ((-?)(\d+).(\d+)) .* 15:00 (\d+)亿 ((-?)(\d+).(\d+))/;
        print $1," ", $2, " ", $6, " ", $7, " ", $11, " ", $12 ;
        print sfile $1, " | ",$2, " | ", $6, " | ", $7, " | ", $11," | ", $12, " | ", " | |\n";
        print "\n";
    }
}

close file;



