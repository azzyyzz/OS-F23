#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <ctype.h>
#include <unistd.h>

#define FILE_SIZE (500 * 1024 * 1024)

int main() {
    int fd = open("text.txt", O_CREAT | O_RDWR, S_IRUSR | S_IWUSR);
    char *file_data = mmap(NULL, FILE_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);

    for (int i = 0; i < FILE_SIZE; i++) {
        char ch;
        read(open("/dev/random", O_RDONLY), &ch, 1);
        while(!isprint(ch)) {
            read(open("/dev/random", O_RDONLY), &ch, 1);
        }

        if (i!=0 && i % 1024 == 0) {
            file_data[i] = '\n';
            continue;
        }
        file_data[i] = ch;
    }

    int cnt = 0;
    char line[1024];
    int ind = 0;
    while(read(fd, line, 1024)) {
        for (int i = 0; i < 1024; i++) { 
            if (isupper(line[i])) {
                cnt++;
                file_data[ind*1024 + i] = tolower(line[i]);
            }
        }
        ind++;
    }
    // Print the total number of capital letters
    printf("Capital: %d\n", cnt);
    close(fd);

    return 0;
}