#include<stdio.h>
#include<limits.h>
#include<float.h>

int main() {
    unsigned short int v1 = USHRT_MAX;
    signed long int v2 = LONG_MAX;
    float v3 = FLT_MAX;
    double v4 = DBL_MAX;
    printf("Size of unsigned short int - %lu \n\n", sizeof(v1));
    printf("Maximum value of unsigned short int - %hu \n\n", v1);
    printf("Size of unsigned signed long int - %lu \n\n", sizeof(v2));
    printf("Maximum value of signed long int - %li \n\n", v2);
    printf("Size of float - %lu \n\n", sizeof(v3));
    printf("Maximum value of float - %f \n\n", v3);
    printf("Size of double - %lu \n\n", sizeof(v4));
    printf("Maximum value of double - %lf \n\n", v4);
}