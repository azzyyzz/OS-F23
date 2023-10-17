#include<stdio.h>
#include<stdlib.h>
#include<signal.h>
#include<unistd.h>
#include<string.h>
#include<errno.h>
#include<sys/stat.h>

void rd(int signum) {
    FILE* file = fopen("text.txt", "r");
    char mes[256];
    while(fgets(mes, 256, file)) {
        printf("%s", mes);
    }
    fclose(file);
}

void ex(int signum) {
    printf("Process terminating...\n");
    exit(0);
}

int main() {

    setuid(0);

    signal(SIGUSR1, rd);
    signal(SIGUSR2, ex);

    raise(SIGUSR1);

    FILE* IDfile = fopen("agent.pid", "w");

    fprintf(IDfile, "%d\n", getpid());
    fclose(IDfile);

    while(1) {
        sleep(1);
    }

}

