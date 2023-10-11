#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include<stdbool.h>

bool is_prime(int n)
{
    if (n <= 1)
        return false;
    for (int d = 2; d * d <= n; ++d){
        if (n % d == 0)
            return false;
    }
    return true;
}

pthread_mutex_t global_lock = PTHREAD_MUTEX_INITIALIZER;

int k = 0;
int c = 0;

int n = 0;

int get_number_to_check() {
    int ret = k;
    if (k != n)
        k++;
    return ret;
}

int increment_primes() {
    c++;
}


void *check_primes(void *arg){
    while(1) {
        pthread_mutex_lock(&global_lock);
        int num = get_number_to_check();
        pthread_mutex_unlock(&global_lock);
        if (num == n) {
            break;
        }
        pthread_mutex_lock(&global_lock);
        if (is_prime(num)) {
            increment_primes();
        }
        pthread_mutex_unlock(&global_lock);
    }
}

int main (int argc, char *argv[]) {
    n = atoi(argv[1]);
    int m = atoi(argv[2]);

    pthread_t ths[m];

    for (int i = 0; i < m; i ++) {
        pthread_create(&ths[i], NULL, check_primes, NULL);
        pthread_join(ths[i], NULL);
    }

    printf("%d\n", c);

}