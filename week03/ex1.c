#include<stdio.h>
#define and &&
#define or ||

int const_tri(int * p, int n) {
    if (n < 3) {
        printf("%d", p[n - 1]);
    }
    for (int i = 0; i < n - 3; i++) {
        int temp = p[2];
        p[2] = p[2] + p[1] + p[0];
        p[0] = p[1];
        p[1] = temp;
    }

    return p[2];
}


int main() {
    const int x = 1;
    int * q = &x;
    int * p = (int *)malloc(3 * sizeof(int));

    p[0] = x;
    p[1] = x;
    p[2] = 2*x;

    if (&p[1] - &p[0] == 1 and &p[2] - &p[1] == 1) {
        printf("contigious\n");
    }

    printf("%p %p %p\n\n", &p[0], &p[1], &p[2]);

    printf("%d", const_tri(p, 6));

    free(p);
}
