#!/bin/env perl
$id = "sz399001";

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
    $ext=0;
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

