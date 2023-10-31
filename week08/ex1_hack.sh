#!/bin/bash

gcc ex1.c -o ex1 ; ./ex1 &

PID=$(cat /tmp/ex1.pid)
start=$(grep heap /proc/$PID/maps | awk -F " " '{print $1}' | awk -F "-" '{print $1}')
end=$(grep heap /proc/$PID/maps | awk -F " " '{print $1}' | awk -F "-" '{print $2}')

sudo xxd -s 0x$start -l $((0x$end - 0x$start )) /proc/$PID/mem | grep -E -o 'pass:.{0,8}' ; kill $PID
echo "start - $start; end - $end"
$SHELL
