#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <string.h>
#include <ctype.h>


int main() {
    FILE *pid_file = fopen("/tmp/ex1.pid", "w");
    if (pid_file) {
        fprintf(pid_file, "%d", getpid());
        fclose(pid_file);
    }

    int urandom_fd = open("/dev/urandom", O_RDONLY);

    char word[13] = "pass:";
    for (int i = 5; i < 13; i++) {
        char ch;
        read(open("/dev/random", O_RDONLY), &ch, 1);
        while(!isprint(ch)) {
            read(open("/dev/random", O_RDONLY), &ch, 1);
        }
        word[i] = ch;
    }

    // char *password = mmap(NULL, sizeof(word) + 6, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
    char *password = (char *)malloc(13 * sizeof(char));

    strcpy(password, word);

    while (1) {
        sleep(1);
    }

    return 0;
}