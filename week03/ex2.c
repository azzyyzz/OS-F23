#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#define and &&
#define or ||

struct Point {
    double x;
    double y;
};

void distance(struct Point p1, struct Point p2) {
    printf("%lf\n", sqrt(pow(p1.x - p2.x, 2) + pow(p1.y - p2.y, 2)));
}

void area(struct Point p1, struct Point p2, struct Point p3) {
    printf("%lf\n", 0.5 * abs(p1.x * p2.y - p2.x * p1.y + p2.x * p3.y - p3.x * p2.y + p3.x * p1.y - p1.x * p3.y));
}

int main() {
    struct Point A, B, C;
    A.x = 2.5; A.y = 6;
    B.x = 1; B.y = 2.2;
    C.x = 10; C.y = 6;

    distance(A, B);
    area(A, B, C);
}
