gcc ex3.c -o ex3 ; ./ex3 3 &
sleep 5
pstree | grep ex3
printf "\n"
sleep 5
pstree | grep ex3
printf "\n"

./ex3 5 &
sleep 5
pstree | grep ex3
printf "\n"
sleep 10
pstree | grep ex3
printf "\n"

$SHELL
#!/bin/bash
