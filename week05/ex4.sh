#!/bin/bash
gcc ex4.c -o ex4
/bin/time -p -o ex4_res.txt ./ex4 10000000 1
echo >> ex4_res.txt
/bin/time -a -p -o ex4_res.txt ./ex4 10000000 2
echo >> ex4_res.txt
/bin/time -a -p -o ex4_res.txt ./ex4 10000000 4
echo >> ex4_res.txt
/bin/time -a -p -o ex4_res.txt ./ex4 10000000 10
echo >> ex4_res.txt
/bin/time -a -p -o ex4_res.txt ./ex4 10000000 100
$SHELL
