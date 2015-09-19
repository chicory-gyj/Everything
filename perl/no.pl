#!/bin/env perl

$command = `curl "http://qt.gtimg.cn/r=479864314&q=sh601718"`;
print "\n",$command,"\n";
$origin = $command;
$ext = $origin;
$ext =~ /\/(\d+)\/(\d+)~(\d+)~(-?\d+.\d+)~(-?\d+.\d+)/;

print $3,' ',$4, ' ',$5;
