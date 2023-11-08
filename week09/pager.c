#define _GNU_SOURCE
#include<stdio.h>
#include<sys/resource.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<stdbool.h>
#include<sys/mman.h>
#include<fcntl.h>
#include<signal.h>
#include<limits.h>
    

struct PTE {
    bool valid;
    int frame;
    bool dirty;
    int referenced;
    int nfuCnt;
    unsigned char agingCnt;
};

struct PTE* pageTable;
char **RAM;
char **disk;
char *algo;
int accessCnt = 0;
int *isFree;

pid_t pagerPID;
int frames = 0, pages = 0;

// Random page replacement
int rrandom(struct PTE* pageTable) {
    int vic = rand() % frames;
    int ind;
    for (int i = 0 ; i < pages; i ++) {
        if (pageTable[i].frame == vic) {
            return i;
        }
    }
}

// NFU page replacement
int nfu(struct PTE* pageTable) {
    int vic = -1, mn = INT_MAX;
    for (int i = 0; i < pages; i ++) {
        if (pageTable[i].frame != -1) {
            if (pageTable[i].nfuCnt < mn) {
                mn = pageTable[i].nfuCnt;
                vic = i;
            }
        }
    }
    return vic;
}

// Aging page replacement
int aging(struct PTE* pageTable) {
    int vic = -1, mn = INT_MAX;
    for (int i = 0; i < pages; i ++) {
        if (pageTable[i].valid) {
            pageTable[i].agingCnt = pageTable[i].agingCnt >> 1;
            if (pageTable[i].referenced) {
                pageTable[i].agingCnt |= (1 << 7);
                pageTable[i].referenced = 0;
            }
        }
    }

    for (int i = 0; i < pages; i ++) {
        if (pageTable[i].valid) {
            if (pageTable[i].agingCnt < mn) {
                mn = pageTable[i].agingCnt;
                vic = i;
            }
        }
    }
    return vic;
}

void ramArray() {
    printf("RAM array\n");
    for (int i = 0; i < frames; i ++) {
        printf("Frame %d ---> %s\n", i, RAM[i]);
    }
}

void signalHandler(int sign) {
    pid_t PID;
    int load = -1;
    if (sign == SIGUSR1) {
        for (int i = 0; i < pages; i ++) {
            if (pageTable[i].referenced != 0) {
                load = i;
                PID = pageTable[load].referenced;
                printf("-------------------------\n");
                printf("A disk access request from MMU Process (pid=%d)\n", PID);
                printf("Page %d is referenced\n", load);
                break;
            }
        }
        if (load != -1) {
            int freeFrame = -1;
            for (int i = 0; i < frames; i ++) {
                if (isFree[i] == 0) {
                    freeFrame = i;
                    isFree[i] = 1;
                    printf("We can allocate it to free frame %d\n", freeFrame);
                    printf("Copy data from the disk (page=%d) to RAM (frame=%d)\n", load, freeFrame);
                    break;
                }
            }

            if (freeFrame != -1) {
                strcpy(RAM[freeFrame], disk[load]);
                pageTable[load].dirty = false;
                pageTable[load].frame = freeFrame;
                pageTable[load].referenced = 0;
                pageTable[load].valid = true;
            } else {
                int victim;
                if (!strcmp(algo, "random")) {
                    victim = rrandom(pageTable);
                } else if (!strcmp(algo, "nfu")) {
                    victim = nfu(pageTable);
                } else {
                    victim = aging(pageTable);
                }
                isFree[victim] = 0;
                printf("We do not have free frames in RAM\n");
                printf("Chose a random victim page %d using %s replacement\n", victim, algo);
                printf("Replace/Evict it with page %d to be allocated to frame %d\n", load, victim);
                printf("Copy data from the disk (page=%d) to RAM (frame=%d)\n", load, victim);

                strcpy(RAM[pageTable[victim].frame], disk[load]);

                pageTable[load].dirty = false;
                pageTable[load].frame = pageTable[victim].frame;
                pageTable[load].referenced = 0;
                pageTable[load].valid = true;

                pageTable[victim].dirty = false;
                pageTable[victim].frame = -1;
                pageTable[victim].referenced = 0;
                pageTable[victim].valid = false;
                pageTable[victim].agingCnt = 0;
                pageTable[victim].nfuCnt = 0;

                isFree[victim] = 1;
                //accessCnt++;
                printf("HEHEHEA\n");
            }
            accessCnt++;
            ramArray();
            printf("%d disk accesses in total\n", accessCnt);
            printf("Resume MMU process\n");
            kill(PID, SIGCONT);
        } else {
            printf("%d disk accesses in total\n", accessCnt);
            printf("Pager is terminated\n");
            exit(0);
        }
    }
}


int main(int argc, char* argv[]) {
    pages = atoi(argv[1]);
    frames = atoi(argv[2]);
    algo = argv[3];

    FILE *pid_file = fopen("/tmp/ex2.pid", "w");
    if (pid_file) {
        fprintf(pid_file, "%d", getpid());
        fclose(pid_file);
    }

    int fl = open("/tmp/ex2/pagetable", O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);

    ftruncate(fl, pages * sizeof(struct PTE));
    pageTable = (struct PTE*)mmap(NULL, pages * sizeof(struct PTE), PROT_READ | PROT_WRITE, MAP_SHARED, fl, 0);

    disk = (char**)malloc(pages * sizeof(char*));

    RAM = (char **)malloc(frames * sizeof(char*));

    isFree = (int*)malloc(frames * sizeof(int));
    isFree[0] = 0;

    signal(SIGUSR1, signalHandler);

    printf("-------------------------\n");
    printf("Initialize page table\n");
    for (int i = 0; i < pages; i ++) {
        pageTable[i].valid = false;
        pageTable[i].frame = -1;
        pageTable[i].dirty = false;
        pageTable[i].referenced = 0;
        pageTable[i].nfuCnt = 0;
        pageTable[i].agingCnt = 0;

        printf("Page %d ---> valid=%d, frame=%d, dirty=%d, referenced=%d\n", i, pageTable[i].valid, pageTable[i].frame, pageTable[i].dirty, pageTable[i].referenced);
    }

    printf("-------------------------\n");
    printf("Initialize RAM:\n");
    for (int i = 0; i < frames; i ++) {
        RAM[i] = (char*)malloc(8 * sizeof(char));
    }
    ramArray();

    printf("-------------------------\n");
    printf("Initialized disk\n");
    for (int i = 0; i < pages; i ++) {
        char *randd = (char*)malloc(8 * sizeof(char));;
        for (int j = 0; j < 8; j ++) {
            randd[j] = (rand() % 60) + 33;
        }
        printf("Page %d ----> %s\n", i, randd);
        //disk[i] = (char*)malloc(8 * sizeof(char));
        disk[i] = randd;
    }
    while(1) {
        sleep(1);
    }

}