#!/bin/env perl
$id = "sh000001";
$filename = "/samba/";
$filename .=$id;
$filename .=".org";
open file ,"<","$filename";

$stockfile = '~/github/fabius8.github.io/stock/stock.org';
open sfile ,">>$stockfile";

while(<file>)
{
    if($_ =~ s/\* //)
    {
        $date = $_;
        print $_;
    }
    else
    {
        $_ =~ /09:29 (\d+)亿 ((-?)(\d+).(\d+)) .* 11:30 (\d+)亿 ((-?)(\d+).(\d+)) .* 15:00 (\d+)亿 ((-?)(\d+).(\d+))/;
        print $1," ", $2, " ", $3, " ", $4, " ", $5, " ", $6 ;
        print "\n";
    }
}

close file;



