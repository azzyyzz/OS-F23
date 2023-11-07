#!/bin/bash

mkdir -p /tmp/ex2
touch /tmp/ex2/pagetable

gcc mmu.c -o mmu
gcc pager.c -o pager

./pager $1 $2 &
sleep 1

PID=$(cat /tmp/ex2.pid)

gnome-terminal -- sh -c "./mmu $1 \"R0 R1 W1 R0 R2 W2 R0 R3 W2\" $PID && $SHELL"

$SHELL
