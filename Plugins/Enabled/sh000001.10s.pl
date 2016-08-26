#!/usr/bin/env perl
$id = "sh000001";

$command = `curl -s --retry 3 "http://qt.gtimg.cn/r=479864314&q=$id"`;

$origin = $command;
$ext = $origin;
$ext =~ /M\/(\d+)\/(\d+)~(\d+)~(-?(\d+).(\d+))~((-?)(\d+).(\d+))/;
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
print $vol,"亿 $ext ";




