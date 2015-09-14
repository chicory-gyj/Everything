#!/bin/env perl
$command = `curl "http://qt.gtimg.cn/r=479864314&q=sh000001"`;
print "\n",$command,"\n";
$origin = $command;
$ext = $origin;
$ext =~ /M\/(\d+)\/(\d+)~(\d+)~(-?(\d+).(\d+))~((-?)(\d+).(\d+))/;
#$ext =~ /S\/(\d+)\/(\d+)~(\d+)~(-?(\d+).(\d+))~(-?(\d+).(\d+))/;

print $4,' ',$5,' ',$6,' ',$7,' ',$8, ' ',$9, ' ',$10;
