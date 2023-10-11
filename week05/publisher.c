#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>
#include<sys/wait.h>
#include<sys/stat.h>
#include<fcntl.h>

int main(int argc, char *argv[]) {
    int n = atoi(argv[1]);
    int pi, ploc;

    char message[1024];
    mkfifo("local", 0666);
    while(1){
        printf("Input message: ");
        fgets(message, 1024, stdin);
        for (int i = 1; i <= n; i++ ) {
            if (fork() == 0) {
                char print_mes[1024];
                ploc = open("local", O_RDONLY);
                read(ploc, print_mes, 1024);
                close(ploc);

                char path[32];
                snprintf(path, sizeof(path), "/tmp/ex1/s%d", i);
                pi = open(path, O_WRONLY);
                write(pi, print_mes, 1024);

                close(pi);

                exit(0);
            } else {
                ploc = open("local", O_WRONLY);
                write(ploc, message, 1024);
                close(ploc);
                wait(NULL);
            }
        }
    }
}