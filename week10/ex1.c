#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <dirent.h>

char * folder;


void find_all_hlinks(const char *file1) {
    struct stat file1_stat;
    lstat(file1, &file1_stat);

    DIR *dir = opendir(".");

    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL) {
        if (entry->d_ino == file1_stat.st_ino && entry->d_type == DT_REG) {
            char path[PATH_MAX];
            realpath(entry->d_name, path);
            printf("Found: inode: %lu, Path: %s\n", entry->d_ino, path);
        }
    }

    closedir(dir);
}

void unlink_all(const char *file1) {
    struct stat file1_stat;
    lstat(file1, &file1_stat) ;

    DIR *dir = opendir(".");

    char last[PATH_MAX];
    int found = 0;


    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL) {
        if (entry->d_ino == file1_stat.st_ino && entry->d_type == DT_REG) {
            char path[PATH_MAX];
            realpath(entry->d_name, path);

            if (found == 0) {
                strcpy(last, path);
                found = 1;
            } else {
                unlink(path);
            }
        }
    }

    closedir(dir);

    printf("Last hard link: %s\n", last);
}

int main(int argc, char *argv[]) {

    folder = argv[1];
    mkdir(folder, S_IRWXU | S_IRWXG | S_IRWXO);
    chdir(folder);

    char file1[PATH_MAX] = "myfile1.txt";
    char file11[PATH_MAX] = "myfile11.txt";
    char file12[PATH_MAX] = "myfile12.txt";
    char file13[PATH_MAX] = "myfile13.txt";
    realpath(file1, file1);
    realpath(file11, file11);
    realpath(file12, file12);
    realpath(file13, file13);


    FILE *File1 = fopen(file1, "w");
    fprintf(File1, "Hello World.");
    fclose(File1);

    link(file1, file11);
    link(file1, file12);

    printf("Hard links to %s:\n", file1);
    find_all_hlinks(file1);

    printf("Moving %s to /tmp/%s\n", file1, file1);
    if (rename(file1, "/tmp/myfile1.txt") == -1) {
        perror("rename");
        exit(EXIT_FAILURE);
    }
    strcpy(file1, "/tmp/file1.txt");

    printf("Modifying %s\n", file11);
    File1 = fopen(file11, "w");
    fprintf(File1, "file11 modified");
    fclose(File1);

    printf("Creating symbolic link %s", file13);
    symlink(file1, file13);

    printf("Modifying /tmp/myfile1.txt\n");
    File1 = fopen(file1, "w");
    fprintf(File1, "Modifying file1, again...");
    fclose(File1);

    printf("Removing duplicates of hard links to %s.\n", file11);
    unlink_all(file11);

    return 0;
}
