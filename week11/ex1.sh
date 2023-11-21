#!/bin/bash

#Creating a file with size 50 MiB
fallocate "lofs.img" -l "50M"

#Setting up a loop device on the created file
looop=$(sudo losetup --find --show "lofs.img")

#Creating a Loop File System (LOFS) ext4
sudo mkfs -t ext4 "$looop"

#Creating a new directory
mkdir -p ./lofsdisk

#Mounting the created filesystem on the mount point ./lofsdisk
sudo mount "$looop" ./lofsdisk

#Add file1 and file2 to the LOFS
sudo bash -c 'echo "Azizullo" > ./lofsdisk/file1'
sudo bash -c 'echo "Sadriddinzoda" > ./lofsdisk/file2'

#Creating directories for the shared libraries
sudo mkdir -p ./lofsdisk/bin

#Function for getting the shared libraries
get_libs() {
    ldd "$1"
}


#Add shared libraries to the lofs, and becuase ldd gives not only the pathes, but also some other stuff which 
#we do not need. That is why using cp can give us error, and to avoid that I am forwarding them to errors_log.txt
sudo cp "/bin/bash" ./lofsdisk/bin 2>erro_logs.txt
sudo cp -v --parents $(get_libs "/bin/bash") lofsdisk 2>erro_logs.txt
sudo cp "/bin/cat" ./lofsdisk/bin 2>erro_logs.txt
sudo cp -v --parents $(get_libs "/bin/bash") lofsdisk 2>erro_logs.txt
sudo cp "/bin/cat" ./lofsdisk/bin 2>erro_logs.txt
sudo cp -v --parents $(get_libs "/bin/bash") lofsdisk 2>erro_logs.txt
sudo cp "/bin/ls" ./lofsdisk/bin 2>erro_logs.txt
sudo cp -v --parents $(get_libs "/bin/bash") lofsdisk 2>erro_logs.txt




sudo gcc ex1.c -o lofsdisk/ex1

sudo chroot lofsdisk ./ex1 > ex1.txt
echo "" >> ex1.txt
./lofsdisk/ex1 >> ex1.txt

$SHELL
