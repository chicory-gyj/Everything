#!/bin/bash
#
#   Copyright (C) 2016 GBCOM
#
# This program is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License version 3 as
# published by the Free Software Foundation.
#
YELLOW='\033[0;33m'
NC='\033[0m'
redis_cluster_tool=`which redis-cluster-tool`
gatewayList="10.60.123.222;10.60.1.20;10.60.123.111"
#gatewayList=`nvramcli get dhcp_failover_cgw_list`
cluster_create_command="$redis_cluster_tool -C \"cluster_create"
masterPort=7001
slavePort=7002
ipList=
ipNum=

### Need one parameter $1
fn_check_cluster_create_result () {
    if [[ $1 == *"Cluster created success!"* ]]; then
        # OK
        return 0
    else
        # FAIL
        return 1
    fi
}

### If you create cluster nodes fail, destroy them and retry
fn_cluster_create () {
    echo $cluster_create_command
    local result=$(eval $cluster_create_command)
    echo -e "${YELLOW}$result${NC}"
    fn_check_cluster_create_result "$result"
    if [[ $? == 0 ]]; then
        # OK Nothing
        return 0
    else
        # fail
        sleep 3
        echo -e "${YELLOW}Retry !!! You Need Check Redis Configure!${NC}"
        fn_cluster_destroy
        fn_cluster_create
    fi
}

fn_cluster_destroy () {
    local cluster_destroy_command=
    for index in `seq 1 $ipNum`
    do
        echo $index
        master_addr="${ipList[$index-1]}:$masterPort"
        echo $master_addr

        cluster_destroy_command="yes yes | \
                                 $redis_cluster_tool -a $master_addr \
                                 -C \"cluster_destroy\""
        eval $cluster_destroy_command
    done
}

#############################################################################
############################### START/COMPILE ###############################
#############################################################################

### Calculate how many addresses
IFS=';' read -ra ipList <<< $gatewayList
ipNum=${#ipList[*]}

### Construct the redis cluster create command
for index in `seq 1 $ipNum`
do
    master_addr="${ipList[$index-1]}:$masterPort"
    if [ $index == $ipNum ]; then
        slave_addr="[${ipList[0]}:$slavePort]";
    else
        slave_addr="[${ipList[$index]}:$slavePort]";
    fi
    cluster_create_command+=" $master_addr$slave_addr"
done
cluster_create_command+="\""

### Get the parameters
while [[ $# -gt 0 ]]
do
    key="$1"
    case $key in
        start|stop)
            action=$key
            ;;
        -h)
            cat << EOF
Usage: $0 {start|stop}
EOF
            exit 2
            ;;
    esac
    shift
done

### Run the command
case "$action" in
    start)
        echo "redis cluster configure start..."
        fn_cluster_create
        ;;
    stop)
        echo "redis cluster configure stop..."
        fn_cluster_destroy
        ;;
    *)
        cat << EOF
Usage: $0 {start|stop|-h}
EOF
        ;;
esac
