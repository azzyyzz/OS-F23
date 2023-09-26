#include<stdio.h>
#include<limits.h>
#include<float.h>
#include<string.h>
#include<stdlib.h>
#define and &&
#define or ||

void* aggregate(void* base, size_t size, int n, void* initial_value, void* (*opr)(const void*, const void*)) {
    size_t sz = size / n;

    void * res = malloc(size);

    //memcpy(res, initial_value, size);

    // if (size == sizeof(int)) {
    //     *((int*)res) = *((int*)initial_value);
    // } else {
    //     *((double*)res) = *((double*)initial_value);
    // }

    for (int i = 0; i < n; i++) {
        opr(res, base + i * sz);
    }

    return res;
}

void* add(const void* a, const void* b) {
    if (sizeof(b) == sizeof(int)) {
        *(int *)a += *(int *)b;
    } else {
        *(double *)a += *(double *)b;
    }
}

void* multiply(const void* a, const void* b) {
    if (sizeof(b) == sizeof(int)) {
        *(int *)a *= *(int *)b;
    } else {
        *(double *)a *= *(double *)b;
    }
}

void* max(const void* a, const void* b) {
    if (sizeof(b) == sizeof(int)) {
        if (*(int *)a < *(int *)b) {
            *(int *)a = *(int *)b;
        }
    } else {
        if (*(double *)a < *(double *)b) {
            *(double *)a = *(double *)b;
        }
    }
}

int main() {
    int ar1[5] = {1, 2, 3, 4, 5};
    double ar2[5] = {1.1, 2.2, 3.3, 4.4, 5.5};
    double* ans2;
    int* ans1;

    int initial_value = 0;

    ans1 = aggregate(ar1, sizeof(ar1), 5, &initial_value, add);
    ans2 = aggregate(ar2, sizeof(ar2), 5, &initial_value, add);
    printf("sum %d\n", *ans1);
    printf("sum %lf\n", *ans2);

    initial_value = 1;

    ans1 = aggregate(ar1, sizeof(ar1), 5, &initial_value, multiply);
    ans2 = aggregate(ar2, sizeof(ar2), 5, &initial_value, multiply);
    printf("mutliplication %d\n", *ans1);
    printf("mutliplication %lf\n", *ans2);

    initial_value = INT_MIN;
    ans1 = aggregate(ar1, sizeof(ar1), 5, &initial_value, max);

    initial_value = DBL_MIN;
    ans2 = aggregate(ar2, sizeof(ar2), 5, &initial_value, max);
    printf("max %d\n", *ans1);
    printf("max %lf\n", *ans2);
}
