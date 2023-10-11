#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<pthread.h>
#include<sys/wait.h>

int main() {
    int pi[2];
    pipe(pi);
    char message[1024];
    
    if (fork() == 0) {
        char print_mes[1024];
        close(pi[1]);
        read(pi[0], print_mes, 1024);
        printf("message is - %s", print_mes);
    } else {
        close(pi[0]);
        printf("input message - ");
        fgets(message, 1024, stdin);
        //scanf("%s", message);
        write(pi[1], message, 1024);
    }
}