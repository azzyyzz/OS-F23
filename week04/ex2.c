#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>

int dot_prod(int u[120], int v[120], int  beg, int end) {
    int res = 0;
    for (int i = beg; i < end; i++ ) {
        res += u[i] * v[i];
    }
    return res;
}

int main() {
    int u[120];
    int v[120];

    for (int i = 0; i < 120; i ++ ) {
        u[i] = rand() % 100;
        v[i] = rand() % 100;
    }

    int n;
    printf("n - ");
    scanf("%d", &n);

    FILE* rd, *wr;

    rd = fopen("temp.txt", "r");
    wr = fopen("temp.txt", "w");

    for (int i = 0; i < n; i ++ ) {

        if (fork() == 0) {
            int beg = i * 120 / n;
            int end = beg + 120 / n;
            int res = 0;
            for (int j = beg; j < end; j ++ ) {
                res += u[j] * v[j];
            }

            fprintf(wr, "%d\n", res);
            exit(0);

        }
    }

    for (int i = 0; i < n; i ++ ) {
        wait(NULL);
    }

    int ln = 0;;
    int total = 0;
    for (int i = 0; i < n; i ++ ) {
        fscanf(rd, "%d", &ln);
        total += ln;
    }

    printf("total %d\n", total);


}