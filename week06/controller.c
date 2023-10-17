#include<stdio.h>
#include<stdlib.h>
#include<signal.h>
#include<string.h>

int pid;

void sigterm(int signum) {
    kill(pid, SIGTERM);
    exit(0);
}

int main() {
    FILE* IDfile = fopen("agent.pid", "r");
    fscanf(IDfile, "%d", &pid);

    if (pid == EOF) {
        printf("Error: No agent found.\n");
        exit(0);
    }
    printf("Agent found. PID: %d.\n", pid);

    signal(SIGINT, sigterm);

    while(1) {
        char command[10];
        printf("Choose a command {\"read\", \"exit\", \"stop\", \"continue\"} to send to agent: ");
        scanf("%s", command);
    
        if (!strcmp("read", command)) {
            kill(pid, SIGUSR1);
        } else if (!strcmp("exit", command)) {
            kill(pid, SIGUSR2);
            exit(0);
        } else if (!strcmp("stop", command)) {
            kill(pid, SIGSTOP);
        } else {
            kill(pid, SIGCONT);
        }
    }

}

