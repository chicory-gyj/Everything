#!/usr/bin/env perl

# 上证
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

# 个股
$id = "sz002568";
$command = `curl -s --retry 3 "http://qt.gtimg.cn/r=479864314&q=$id"`;
$origin = $command;
$ext = $origin;
$ext =~ /\/(\d+)\/(\d+)~(\d+)~(-?\d+.\d+)~(-?\d+.\d+)/;
$ext = $5;
if($ext==NULL)
{
    $ext=0;
}
$command =~ /(\d+)~(\d+).(\d+)~(\d+).(\d+)~~/;
$vol = $2;
$vol = $2/100;
$vol =~ /(\d+)./;
$vol = $1;
if($vol == NULL)
{
    $vol = 0;
}
print " ",$vol,"万 $ext";





