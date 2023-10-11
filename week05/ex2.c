#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<pthread.h>
#include<sys/wait.h>
#include<pthread.h>


struct Thread
{
    pthread_t id;
    int i;
    char message[256];
};

void *printMessage(void* th) {
    printf("%s", ((struct Thread *)th)->message);
    pthread_exit(NULL);
}

int main() {

    int n;
    printf("Type n: ");
    scanf("%d", &n);

    struct Thread ths[n];

    for (int i = 0; i < n; i ++) {
        ths[i].i = i;
        sprintf(ths[i].message, "Hello from thread %d\n", ths[i].i);
        printf("Thread %d is created\n", ths[i].i);
        pthread_create(&ths[i].id, NULL, printMessage, &ths[i]);
        pthread_join(ths[i].id, NULL);
        printf("Thread %d exits\n\n", ths[i].i);
    }
}