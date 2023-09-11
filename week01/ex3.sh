mkdir ~/week01/folder1

date
sleep 3
mkdir ~/week01/folder2

date
sleep 3
touch ~/week01/folder1/root.txt

date
sleep 3
touch ~/week01/folder2/home.txt

ls / -c -r > ~/week01/folder1/root.txt
cat ~/week01/folder1/root.txt
ls ~/week01/folder1

ls ~ -c -r > ~/week01/folder2/home.txt
cat ~/week01/folder2/home.txt
ls ~/week01/folder2
