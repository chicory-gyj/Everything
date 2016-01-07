#!/bin/env perl
$id = "sh000001";

$filename = "/samba/";
$filename .=$id;
$filename .=".org";

open file ,">>$filename";
$time = `date "+%H%M"`;
$day = `date "+%Y.%m.%d"`;
$hour = `date "+%H"`;

$cmd = `tail -n 1 $filename`;
print $cmd;
$cmd =~ /:(\d+) (\d+)亿 (-?\d+.\d+) \+(\d+) $/;
$last = $2;
if($last == NULL)
{
    $last =0;
}
print "haha ",$2," 11";
if($time == "0915")
{
    print file "\n* ",$day;
}
if(($time >= "0925" && $time <= "1131") || ($time >= "1300" && $time <= "1501"))
{
    goto good;
}
else
{
    print $time;
    exit
}

good:
$command = `curl --retry 3 "http://qt.gtimg.cn/r=479864314&q=$id"`;
print "\n",$command,"\n";
$origin = $command;
$ext = $origin;
$ext =~ /M\/(\d+)\/(\d+)~(\d+)~(-?(\d+).(\d+))~((-?)(\d+).(\d+))/;
print $7;
$ext = $7;
if($ext==NULL)
{
    $ext="0.00";
}
$command =~ /~(\d+)~~~~/;
$vol = $1/10000;
$vol =~ /(\d+)./;
$vol = $1;
if($vol == NULL)
{
    $vol = 0;
}
$delta = $vol - $last;
$date = `date "+%H:%M"`;
chomp($date);
print file $date," ", $vol,"亿 $ext ","+",$delta," ";



# end
# i want save it to stock.org

$stockfile = '/home/fabius8/github/fabius8.github.io/stock/stock.org';

if( -e $stockfile )
{
    print "exist stork.org!";
}
else
{
    goto NOFILE;
}

open sfile ,">>$stockfile";
if($time == "0929")
{
    chomp($day);
    $OPEN = $vol;
    $HOW = $ext;
    print sfile "| ",$day, " | ",$OPEN, " | ",$HOW, " | ";
}
if($time == "1130")
{
    $VOL1 = $vol;
    $EXT1 = $ext;
    print sfile $VOL1, " | ", $EXT1, " | ";
}
if($time == "1500")
{
    $VOL2 = $vol;
    $EXT2 = $ext;
    print sfile $VOL2, " | ", $EXT2, " | | |\n";
}

exit;

NOFILE:
print "no stock file!";
