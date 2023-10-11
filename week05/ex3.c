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

int primes_count(int a, int b)
{
    int ret = 0;
    for (int i = a; i < b; ++i)
        if (is_prime(i))
            ret++;
    return ret;
}

typedef struct prime_request
{
    int a, b;
} prime_request;

void *prime_counter(void *arg)
{
    prime_request req = *(prime_request *)arg;
    int* count = malloc(sizeof(int));
    *count = primes_count(req.a, req.b); 
    return ((void *)count);
}

int main (int argc, char *argv[]) {
    int n = atoi(argv[1]);
    int m = atoi(argv[2]);
    void* ret;
    int res = 0;

    pthread_t ths[m];

    for (int i = 0; i < m; i ++) {
        struct prime_request prq;
        prq.a = (n / m) * i;
        if (i != m - 1) {
            prq.b = (i + 1) * (n / m);
        } else {
            prq.b = n;
        }
        pthread_create(&ths[i], NULL, prime_counter, &prq);
        pthread_join(ths[i], &ret);
        res += *(int *) ret;
    }

    printf("%d\n", res);

}