#!/bin/env perl
$stockid = "sz399006";
$filename = "/samba/";
$stockfile = "/samba/";

$filename .= $stockid;
$filename .= ".org";
open file ,"<","$filename";

$stockfile .= $stockid;
$stockfile .= "_cov.org";
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
        $VOL0 = $1;
        $EXT0 = $2;
        $VOL1 = $6;
        $EXT1 = $7;
        $VOL2 = $11 - $6;
        $EXT2 = $12 - $7;
        $VOLSUM = $11;
        $EXTSUM = $12;
        print sfile $VOL0, " | ",$EXT0, " | ", $VOL1, " | ", $EXT1, " | ", $VOL2," | ", $EXT2, " | ", $VOLSUM," | ", $EXTSUM," |\n";
        print "\n";
    }
}

close file;



