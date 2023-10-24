#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>

#define MAX 10000000

unsigned int arr[MAX] = {0};

void allocateFirstFit(unsigned int adrs, int size) {
    for (int i = 0; i < MAX; i++) {
        if (arr[i] == 0) {
            bool chk = true;
            if (arr[i + size - 1] != 0) {
                chk = false;
            }
            if (chk) {
                for (int j = 0; j < size; j++) {
                    arr[i + j] = adrs;
                }
                return;
            }
        }
    }
}

void allocateBestFit(unsigned int adrs, int size) {
    int best = -1;
    int bestsz = MAX + 1;

    int cur = -1;
    int cursz = 0;

    for (int i = 0; i < MAX; i++) {
        if (arr[i] == 0) {
            if (cur == -1) {
                cur = i;
            }
            cursz++;
        } else {
            if (cursz >= size && cursz < bestsz) {
                best = cur;
                bestsz = cursz;
            }
            cur = -1;
            cursz = 0;
        }
    }

    if (cursz >= size && cursz < bestsz) {
        best = cur;
    }


    if (best != -1) {
        for (int i = best; i < best + size; i++) {
            arr[i] = adrs;
        }
    }
}

void allocateWorstFit(unsigned int adrs, int size) {
    int worst = -1;
    int worstsz = 0;

    int cur = -1;
    int cursz = 0;

    for (int i = 0; i < MAX; i++) {
        if (arr[i] == 0) {
            if (cur == -1) {
                cur = i;
            }
            cursz++;
        } else {
            if (cursz > worstsz) {
                worst = cur;
                worstsz = cursz;
            }
            cur = -1;
            cursz = 0;
        }
    }

    if (cursz > worstsz) {
        worst = cur;
    }

    if (worst != -1) {
        for (int i = worst; i < worst + size; i++) {
            arr[i] = adrs;
        }
    }
}

void clear(unsigned int adrs) {
    for (int i = 0; i < MAX; i++) {
        if (arr[i] == adrs) {
            arr[i] = 0;
        }
    }
}

void reset() {
    for (int i = 0; i < MAX; i++) {
        arr[i] = 0;
    }
}

int main() {
    FILE *file = fopen("queries.txt", "r");
    if (file == NULL) {
        printf("File 'queries.txt' not found.\n");
        return 1;
    }

    clock_t start_time, end_time;
    double total_time = (double)(end_time - start_time) / CLOCKS_PER_SEC;
    double throughput = total_time / MAX;
    char line[64], lines[1000][64];
    int lines_ind = 0;

    while(fgets(lines[lines_ind++], sizeof(lines[lines_ind]), file));

    for (int i = 0; i < 3; i ++) {
        start_time = clock();
        for (int j = 0; j < lines_ind; j++) {
            char command[64];
            unsigned int adrs;
            int size;

            if (sscanf(lines[j], "allocate %u %d", &adrs, &size) == 2) {
                //printf("IIIII %d\n", i);
                if (i == 0){
                    allocateFirstFit(adrs, size);
                }
                else if (i == 1){
                    allocateBestFit(adrs, size);
                }
                else{
                    allocateWorstFit(adrs, size);
                }
            } else if (sscanf(lines[j], "clear %u", &adrs) == 1) {
                clear(adrs);
            }
        }
        end_time = clock();
        total_time = (double)(end_time - start_time) / CLOCKS_PER_SEC;
        throughput = lines_ind / total_time;
        printf("Throughput: %.5f allocations per second\n", throughput);
        reset();
    }


    fclose(file);
    return 0;
}