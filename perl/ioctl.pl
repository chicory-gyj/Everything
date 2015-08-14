#!/usr/bin/env perl

require "ioctl.ph";
require 'ioctl.ph';
    $getp = &TIOCGETP;
    die "NO TIOCGETP" if $@ || !$getp;
    $sgttyb_t = "ccccs";                # 4 chars and a short
    if (ioctl(STDIN,$getp,$sgttyb)) {
        @ary = unpack($sgttyb_t,$sgttyb);
        $ary[2] = 127;
        $sgttyb = pack($sgttyb_t,@ary);
        ioctl(STDIN,&TIOCSETP,$sgttyb)
            || die "Can't ioctl: $!";
    }
