#!/usr/bin/perl

open FILE,"ps_ac.conf"
 or die "Can't open it";
@ip = grep {/123456/i}<FILE>;
$ip[0] =~ s/123456//;
chomp(@ip);
$wlanacip = $ip[0];
$wlanacip =~ s/^\s+//;
print $wlanacip;
