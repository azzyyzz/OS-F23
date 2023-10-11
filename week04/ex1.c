#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <time.h>

int main() {
    clock_t start_time;

    start_time = clock();

    // Create the first child process
    pid_t fch = fork();

    if (fch > 0) {
        pid_t sch = fork();
        if (sch > 0) {
            printf("Parent PID: %d PPID: %d\n", getpid(), getppid());
            printf("Parent time - %f seconds\n", (double)(clock() - start_time) / CLOCKS_PER_SEC);
        } else if (sch == 0){
            printf("Second child PID: %d PPID: %d\n", getpid(), getppid());
            printf("Second child time - %f seconds\n", (double)(clock() - start_time) / CLOCKS_PER_SEC);
        }
    } else if (fch == 0) {
        printf("First child PID: %d PPID: %d\n", getpid(), getppid());
        printf("First child time - %f seconds\n", (double)(clock() - start_time) / CLOCKS_PER_SEC);
    }
}