#include<stdio.h>
#include<sys/resource.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>

#define MB10 100 * 1024 * 1024

int main() {
    char* mem[10];
    struct rusage usage;

    for (int i = 0; i < 10; i ++) {
        mem[i] = malloc(MB10 * sizeof(char));
        memset(mem[i], '0', MB10);
        getrusage(RUSAGE_SELF, &usage);
        printf("Memory usage %d: %ld\n", i, usage.ru_maxrss);
        sleep(1);
    }

    for (int i = 0; i < 10; i ++) {
        free(mem[i]);
    }
}