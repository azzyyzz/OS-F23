#!/bin/bash
mkdir /tmp/ex1
gcc publisher.c -o publisher
gcc subscriber.c -o subscriber

N=$1

gnome-terminal -- ./publisher $N

for ((i=1; i<=$N; i++))
do
	gnome-terminal -- ./subscriber $i
done

$SHELL
