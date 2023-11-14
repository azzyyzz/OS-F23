gcc monitor.c -o monitor
gcc ex1.c -o ex1
mkdir -p $1
# monitor.c shows stats if it gets SIGINT, but it immediately closes the window. I did not find out how to fix it.
gnome-terminal -- sh -c "./monitor $1 && $SHELL"
gnome-terminal -- sh -c "./ex1 $1 && $SHELL"
