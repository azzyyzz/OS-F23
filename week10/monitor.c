#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <limits.h>
#include <signal.h>
#include <sys/inotify.h>
#include <sys/stat.h>
#include <dirent.h>
#include <fcntl.h>

#define EVENT_SIZE (sizeof(struct inotify_event))
#define BUF_LEN (1024 * (EVENT_SIZE + 16))

void print_stat_info(const char *path) {
    struct stat st;
    if (stat(path, &st) == 0) {
        printf("Info for %s:\n", path);
        printf("  mode: %o\n", st.st_mode);
        printf("  ize: %lld\n", (long long)st.st_size);
    }
}

void handle_signal(int signum) {
    printf("Terminating.\n");

    DIR *dir = opendir(".");

    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL) {
        if (strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0) {
            char path[PATH_MAX];
            snprintf(path, sizeof(path), "%s/%s", ".", entry->d_name);
            print_stat_info(path);
        }
    }

    closedir(dir);
    exit(0);
}

void process_event(struct inotify_event *event, const char *path) {
    if (event->mask & IN_ACCESS) {
        printf("File %s was accessed.\n", path);
    }
    if (event->mask & IN_CREATE) {
        if (event->mask & IN_ISDIR){
            printf("Directory %s was created.\n", path);
        } else{
            printf("File %s was created.\n", path);
        }
    }
    if (event->mask & IN_DELETE) {
        if (event->mask & IN_ISDIR){
            printf("Directory %s was created.\n", path);
        } else{
            printf("File %s was created.\n", path);
        }
    }
    if (event->mask & IN_MODIFY) {
        printf("File %s was modified.\n", path);
    }
    if (event->mask & IN_OPEN) {
        if (event->mask & IN_ISDIR){
            printf("Directory %s was created.\n", path);
        } else{
            printf("File %s was created.\n", path);
        }
    }
    if (event->mask & IN_ATTRIB) {
        printf("Metadata of %s changed.\n", path);
    }
}

int main(int argc, char *argv[]) {
    signal(SIGINT, handle_signal);

    int inotifier = inotify_init();

    int watcher = inotify_add_watch(inotifier, argv[1], 
        IN_ACCESS | IN_CREATE | IN_DELETE | IN_MODIFY | IN_OPEN | IN_ATTRIB);

    DIR *dir = opendir(argv[1]);

    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL) {
        if (strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0) {
            char path[PATH_MAX];
            snprintf(path, sizeof(path), "%s/%s", argv[1], entry->d_name);
        }
    }

    closedir(dir);

    char buf[BUF_LEN];

    while (1) {
        ssize_t len = read(inotifier, buf, BUF_LEN);

        struct inotify_event *event = (struct inotify_event *)buf;
        while ((char *)event < buf + len) {
            if (event->len) {
                char path[PATH_MAX];
                snprintf(path, sizeof(path), "%s/%s", argv[1], event->name);
                process_event(event, path);
            }
            event = (struct inotify_event *)((char *)event + EVENT_SIZE + event->len);
        }
    }
    close(inotifier);

    return 0;
}
