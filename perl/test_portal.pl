#!/usr/bin/env perl

my ($file, $url, $command, @linei, $filename);
$filename = "/usr/local/ac/config/portal.conf";
open $file ,"<", $filename;
@line = <$file>;
chomp(@line);
while(@line)
{
    $url = shift (@line);
    print $url; 
    print "\n"; 
    if($url =~ /portal.url=/)
    {
        $url =~ s/portal.url=//;
        print $url; 
        goto skip;
    }
}

skip:
$command = "curl -m 2 $url 2>&1";
print $command;

$line = `$command`;
print $line;
if($line =~ /curl: \(/)
{
    print "wrong";
    system("/usr/local/ac/conf/portalctl set");
}
else
{
    print "right";
}
close $file;
