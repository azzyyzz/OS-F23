#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct File {
    char *id;
    char name[63];
    size_t size;
    char data[1024];
    struct Directory* directory;
};

struct Directory {
    char name[63];
    struct File files[100];
    struct Directory* directories[100];
    unsigned char nf;
    unsigned char nd;
    char path[2048];
};

void overwrite_to_file(struct File* file, const char* str) {
    strncpy(file->data, str, 1024);
    file->size = strlen(file->data) + 1;
}

void append_to_file(struct File* file, const char* str) {
    size_t currentSize = strlen(file->data);
    strncat(file->data, str, 1024 - currentSize - 1);
    file->size = strlen(file->data) + 1;
}

void printp_file(struct File* file) {
    printf("%s/%s\n", file->directory->path, file->name);
}

void add_file(struct File* file, struct Directory* dir) {
    dir->files[dir->nf] = *file;
    file->directory = dir;
    dir->nf++;
}

int main() {
    struct Directory root;
    strcpy(root.name, "/");
    root.nf = 0;
    root.nd = 0;
    strcpy(root.path, "/");

    struct Directory home;
    strcpy(home.name, "home");
    home.nf = 0;
    home.nd = 0;
    strcpy(home.path, "/home");

    struct Directory bin;
    strcpy(bin.name, "bin");
    bin.nf = 0;
    bin.nd = 0;
    strcpy(bin.path, "/bin");

    struct File bash;
    bash.id = "0";
    strcpy(bash.name, "bash");
    bash.size = 20; 
    strcpy(bash.data, "Bourne Again Shell!!");
    bash.directory = &bin;

    add_file(&bash, &bin);

    struct File ex3_1;
    ex3_1.id = "1";
    strcpy(ex3_1.name, "ex3_1.c");
    ex3_1.size = 28; 
    strcpy(ex3_1.data, "int printf(const char * format, ...);");
    ex3_1.directory = &home;

    struct File ex3_2;
    ex3_2.id = "2";
    strcpy(ex3_2.name, "ex3_2.c");
    ex3_2.size = 31; 
    strcpy(ex3_2.data, "// This is a comment in C language");
    ex3_2.directory = &home;

    add_file(&ex3_1, &home);
    add_file(&ex3_2, &home);

    append_to_file(&ex3_1, "int main(){printf(\"Hello World!\");}");

    printp_file(&bash);
    printp_file(&ex3_1);
    printp_file(&ex3_2);

    return 0;
}