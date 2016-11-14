#!/bin/bash

FILEIMG="/mnt/failover.img"
if [ ! -f ${FILEIMG} ]; then
	touch ${FILEIMG}
	dd if=/dev/zero of=${FILEIMG} bs=1M count=50
	yes|mkfs.ext3 ${FILEIMG}
fi

FILEDIR="/mnt/failover"
if [ ! -d ${FILEDIR} ]; then
	mkdir ${FILEDIR}
	mount -o rw,loop,relatime ${FILEIMG} ${FILEDIR}
fi
