#!/bin/bash
touch ex5.txt
chmod a-w ex5.txt
chmod u=rwx ex5.txt
chmod o=rwx ex5.txt
chmod g=u ex5.txt

# 660 means rw- for user, rw- for groups, and --- for others
# 775 means rwx for user, rwx for groups, and r-x for others
# 777 measn rwx for user, rwx for groups, and rwx for others
# To better understand how it works we can imagine every digit of these numbers as binaries. 660 -> 110 110 000, 775 -> 111 111 101, 777 -> 111 111 111. For example 110 means file can be read, written, but not executed.

$SHELL
