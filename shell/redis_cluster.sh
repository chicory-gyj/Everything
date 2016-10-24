#!/bin/bash
#
#   Copyright (C) 2016 GBCOM
#
# This program is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License version 3 as
# published by the Free Software Foundation.
#

while [[ $# > 0 ]]
do
    key="$1"
    case $key in
        start|stop)
            action=$key
            ;;
        *)
            cat << EOF
$"Usage: $0 {start|stop}"
EOF
            exit 2
            ;;
    esac
    shift
done

case "$action" in
    start)
        echo "redis cluster configure start..."
        ;;
    stop)
        echo "redis cluster configure stop..."
        ;;
esac
