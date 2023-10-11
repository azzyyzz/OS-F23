#!/bin/bash
gcc ex3.c -o ex3
/bin/time -p -o ex3_res.txt ./ex3 10000000 1
echo >> ex3_res.txt
/bin/time -a -p -o ex3_res.txt ./ex3 10000000 2
echo >> ex3_res.txt
/bin/time -a -p -o ex3_res.txt ./ex3 10000000 4
echo >> ex3_res.txt
/bin/time -a -p -o ex3_res.txt ./ex3 10000000 10
echo >> ex3_res.txt
/bin/time -a -p -o ex3_res.txt ./ex3 10000000 100
$SHELL
