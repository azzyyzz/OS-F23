#include <stdio.h>

int tribonacci(int n) {
    if (n == 0) return 0;
    if (n <= 2) return 1;

    int a = 0, b = 1, c = 1, d;

    for (int i = 3; i <= n; i++) {
        d = a + b + c;
        a = b;
        b = c;
        c = d;
    }

    return c;
}

int main() {
    int a = tribonacci(4);
    int b = tribonacci(36);

    printf("4 - %d, 36 - %d\n", a, b);

    return 0;
}