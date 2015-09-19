#!/bin/env perl
$id = "sz002494";

$filename = "/samba/";
$filename .=$id;
$filename .=".org";

open file ,">>$filename";
$time = `date "+%H%M"`;
$day = `date "+%Y.%m.%d"`;
$hour = `date "+%H"`;

$cmd = `tail -n 1 $filename`;
print $cmd;
$cmd =~ /:(\d+) (\d+) (-?\d+.\d+) \+(\d+) $/;
$last = $2;
if($last == NULL)
{
    $last = 0;
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
    exit;
}

good:
$command = `curl "http://qt.gtimg.cn/r=479864314&q=$id"`;
$origin = $command;
$ext = $origin;
$ext =~ /\/(\d+)\/(\d+)~(\d+)~(-?\d+.\d+)~(-?\d+.\d+)/;
$ext = $5;
if($ext==NULL)
{
    $ext=0;
}
print "\n",$command,"\n";
$command =~ /(\d+)~(\d+).(\d+)~(\d+).(\d+)~~/;
$vol = $1;
if($vol == NULL)
{
    $vol = 0;
}
$delta = $vol - $last;
$date = `date "+%H:%M"`;
chomp($date);
print file $date," ", $vol," $ext ","+",$delta," ";

