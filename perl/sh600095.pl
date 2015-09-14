#!/bin/env perl

$filename = "/samba/sh600095.org";
open file ,">>$filename";
$time = `date "+%H%M"`;
$day = `date "+%Y.%m.%d"`;
$hour = `date "+%H"`;

$cmd = `tail -n 1 $filename`;
print $cmd;
$cmd =~ /:(\d+) (\d+) \+(\d+) $/;
$last = $2;
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
$command = `curl "http://qt.gtimg.cn/r=479864314&q=sh600095"`;
print "\n",$command,"\n";
$command =~ /(\d+)~(\d+).(\d+)~(\d+).(\d+)~~/;
$vol = $1;
$delta = $vol - $last;
$date = `date "+%H:%M"`;
chomp($date);
print file $date," ", $vol," ","+",$delta," ";

