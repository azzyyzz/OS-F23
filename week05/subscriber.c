#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<pthread.h>
#include<sys/wait.h>
#include<fcntl.h>

int main(int argc, char *argv[]) {
    int id = atoi(argv[1]);
    char path[32];
    snprintf(path, sizeof(path), "/tmp/ex1/s%d", id);
    mkfifo(path, 0666);
    char message[1024];
    int pi;
    while(1){
        pi = open(path, O_RDONLY);
        read(pi, message, 1024);
        printf("Subscriber id - %d. Message - %s\n", id, message);
        close(pi);
    }
}