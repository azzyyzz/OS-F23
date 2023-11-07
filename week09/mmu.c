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

struct PTE {
    bool valid;
    int frame;
    bool dirty;
    int referenced;
    int nfuCnt;
    unsigned char agingCnt;
};

struct PTE *pageTable;
char *RAM;
char *memaccess;
int pages;
int hit = 0, miss = 0;
bool sleeping = true;

pid_t procPID, selfPID;

void pageTableArray() {
    printf("Page table\n");
    for (int i = 0; i < pages; i ++) {
        printf("Page %d ---> valid=%d, frame=%d, dirty=%d, referenced=%d\n", i, pageTable[i].valid, pageTable[i].frame, pageTable[i].dirty, pageTable[i].referenced);
    }
}

void pageFault(int page) {
    if (pageTable[page].valid) {
        printf("It is a valid page\n");
        hit++;
        return;
    }
    miss++;
    
    printf("It is not a valid page --> page fault\n");
    printf("Ask pager to load it from disk (SIGUSR1 signal) and wait\n");
    
    pageTable[page].referenced = selfPID;
    pageTable[page].dirty = false;

    printf("%d\n", procPID);
    kill(procPID, SIGUSR1);
    
    while(sleeping) {
        sleep(1);
    }
    sleeping = true;
    printf("MMU Resumed by SIGCONT signal from pager\n");
}

void signalHandler(int sign) {
    if (sign == SIGCONT) {
        sleeping = false;
    }
}

int main(int argc, char* argv[]) {
    pages = atoi(argv[1]);
    memaccess = argv[2];
    procPID = atoi(argv[3]);
    selfPID = getpid();
    signal(SIGCONT, signalHandler);

    int fl = open("/tmp/ex2/pagetable", O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);

    ftruncate(fl, pages * sizeof(struct PTE));

    pageTable = mmap(NULL, pages * sizeof(struct PTE), PROT_READ | PROT_WRITE, MAP_SHARED, fl, 0);

    
    printf("-------------------------\n");
    printf("Initialized page table\n");
    for (int i = 0; i < pages; i++) {
        pageTable[i].valid = false;
        pageTable[i].frame = -1;
        pageTable[i].dirty = false;
        pageTable[i].referenced = 0;
        pageTable[i].nfuCnt = 0;
        pageTable[i].agingCnt = 0;
    }
    pageTableArray();

    char *op = strtok(memaccess, " ");


    do {
        char opPageS[strlen(op) - 1];
        memset(opPageS, 0, strlen(op));
        for (int i = 1; i < strlen(op); i ++) {
            opPageS[i - 1] = op[i];
        }

        int page = atoi(opPageS);

        pageTable[page].nfuCnt ++;

        printf("-------------------------\n");
        if (op[0] == 'R') {
            printf("Read Request for page %d\n", page);
            pageFault(page);
        } else {
            printf("Write Request for page %d\n", page);
            pageFault(page);
            printf("It is a write request then set the dirty field\n");
            pageTable[page].dirty = true;
        }
        pageTableArray();
        op = strtok(NULL, " ");
    } while(op != NULL);
    printf("Done all requests.\n");
    printf("MMU sends SIGUSR1 to the pager.\n");
    printf("MMU terminates.\n");
    printf("Hits: %d\n", hit);
    printf("Misses: %d\n", miss);
    printf("Hit Ratio: %.2f%\n", hit*100.0/(miss + hit));
    kill(procPID, SIGUSR1);

}