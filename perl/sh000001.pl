#!/bin/env perl
$id = "sh000001";

$filename = "/samba/";
$filename .=$id;
$filename .=".org";

open file ,">>$filename";
$time = `date "+%H%M"`;
$day = `date "+%Y-%m-%d"`;
$hour = `date "+%H"`;


$cmd = `tail -n 1 $filename`;
print $cmd;
$cmd =~ /:(\d+) (\d+)亿 (-?\d+.\d+) \+(\d+) $/;
$last = $2;
if($last == NULL)
{
    $last =0;
}

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
    $week = `date "+%A"`;
    chomp($week);
    chomp($day);
    $OPEN = $vol;
    $HOW = $ext;
    print sfile "| ",$day, " | "," $work | ",$OPEN, " | ",$HOW, " | ";
}
if($time == "1130")
{
    $VOL1 = $vol;
    $EXT1 = $ext;
    print sfile $VOL1, " | ", $EXT1, " | ";
}
if($time == "1500")
{
    $VOL_SUM = $vol;
    $EXT_SUM = $ext;

    $GET_LAST = `tail -n 1 $stockfile`;
    print $GET_LAST;
    $GET_LAST =~ /\|\s+(-?\d+\.\d+)\s+\|\s+(\d+)\s+\|\s+(-?(\d+)\.(\d+))\s+\|/;
    $VOL1 = $2;
    $EXT1 = $3;
    $VOL2 = $VOL_SUM - $VOL1;
    $EXT2 = $EXT_SUM - $EXT1;
    $EXT2 = sprintf "%.2f",$EXT2;
    print "\n\n\n";
    print $VOL1," ", $EXT1;
    print sfile " ",$VOL2, " | ", $EXT2, " | ",$VOL_SUM," | ",$EXT_SUM ," |\n";
    $result = `emacs $stockfile --batch -l ~/.emacs.d/init.el --eval '(progn(org-table-align))' -f save-buffer --kill`;
}

exit;

NOFILE:
print "no stock file!";
