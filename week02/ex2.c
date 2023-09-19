#include<stdio.h>
#include<string.h>

int main() {
    char *in;
    size_t size = 0;
    char out[100];
    int dot = 0;

    getline(&in, &size, stdin);

    for (int i = 0; i < strlen(in); i++){
        if (in[i] == '.') {
            dot = i;
            break;
        }
        out[i] = in[i];
    }

    printf("\"");
    for (int i = dot - 1; i >= 0; i--){
        printf("%c", out[i]);
    }
    printf("\"\n");

}