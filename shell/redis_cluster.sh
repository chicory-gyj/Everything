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
#redis_server=/home/fabius8/cluster-test/redis-server
redis_server=`which redis-server`
redis_cluster_tool=`which redis-cluster-tool`
#gatewayList="10.60.123.222;10.60.1.20;10.60.123.111"
gatewayList=`nvramcli get dhcp_failover_cgw_list`
cluster_create_command="$redis_cluster_tool -C \"cluster_create"
masterPort=7001
slavePort=7002
ipList=
ipNum=
masterRunDir="/opt/redisMaster"
slaveRunDir="/opt/redisSlave"

### Start redis-server
### Input parameter $1:($masterRunDir|$slaveRunDir)
### Input parameter $2:($masterPort|$slavePort)
fn_start_redis_server () {
    mkdir -p $1
    touch $1/redis.conf
    cat <<EOF > "$1/redis.conf"
port $2
cluster-enabled yes
cluster-config-file nodes.conf
cluster-node-timeout 5000
appendonly yes
protected-mode no
daemonize yes
EOF
    cd $1; pwd; $redis_server "$1/redis.conf"
}

### Need one parameter $1:String
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

### Print help information
fn_help () {
        cat << EOF
Usage: $0 {ready|start|stop|restart}

ready:       redis-server startup
start:       redis cluster start configure
stop:        redis cluster stop, all reset
restart:     redis-server restart
             redis cluster reconfigure
             
Tips: If the program is running for the first time,
      it is best to choose to *restart*

EOF
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
        ready|start|stop|restart)
            action=$key
            ;;
        *)
            fn_help
            exit 2
            ;;
    esac
    shift
done

### Run the command
case "$action" in
    ready)
        echo -e "redis-server get ready..."
        fn_start_redis_server $masterRunDir $masterPort
        fn_start_redis_server $slaveRunDir $slavePort
        ;;
    start)
        echo "redis cluster configure start..."
        fn_cluster_create
        ;;
    stop)
        echo "redis cluster configure stop..."
        fn_cluster_destroy
        ;;
    restart)
        echo "redis cluster configure restart..."
        pkill -9 redis-server
        fn_start_redis_server $masterRunDir $masterPort
        fn_start_redis_server $slaveRunDir $slavePort
        fn_cluster_destroy
        fn_cluster_create
        ;;
    *)
        fn_help
        ;;
esac
