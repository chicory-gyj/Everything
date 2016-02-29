#!/bin/env perl
# | 2016-3-1 | ||||      |
#       |
#       |
#       V
# | 2016-3-1 | ||||sunday|

$org_file = "/home/fabius8/github/fabius8.github.io/stock/stock.org";
open file, "<", $org_file;

while(<file>)
{
    #print $_;
    $date = $_;
    $date  =~ /((\d+)-(\d+)-(\d+))/;
    print $1;
    $week = `date -d "$1" +%A`;
    chomp($week);
    print " ",$week, "\n";
    $cmd = "sed -i '/$1/ s#|\\s\\s\\s\\s\\s\\s\\s\\s|#| $week |#g'";
    $cmd .= " ";
    $cmd .= $org_file;

    print "$cmd";
    $result = `$cmd`;
    print "\n";
}

close file;
