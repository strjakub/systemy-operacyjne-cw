#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <sys/stat.h>
#include <time.h>
#include <dirent.h>
#include <string.h>

int cnt_file = 0;
int cnt_dir = 0;
int cnt_spec_char = 0;
int cnt_spec_div = 0;
int cnt_fifo = 0;
int cnt_slink = 0;
int cnt_socket = 0;

void print_info(const char* filename, struct stat *stat){
    printf("===================================\n");
    printf("1) Filename: %s\n", filename);

    char buf[PATH_MAX];
    char* result = realpath(filename, buf);
    printf("2) Absolute Path: %s\n", result);

    if(S_ISREG(stat->st_mode)) {
        printf("3) Type: file\n");
        cnt_file++;
    } else if(S_ISDIR(stat->st_mode)){
        printf("3) Type: directory\n");
        cnt_dir++;
    } else if(S_ISCHR(stat->st_mode)){
        printf("3) Type: char dev\n");
        cnt_spec_char++;
    } else if(S_ISBLK(stat->st_mode)){
        printf("3) Type: block dev\n");
        cnt_spec_div++;
    } else if(S_ISFIFO(stat->st_mode)){
        printf("3) Type: FIFO\n");
        cnt_fifo++;
    } else if(S_ISLNK(stat->st_mode)){
        printf("3) Type: slink\n");
        cnt_slink++;
    } else if(S_ISSOCK(stat->st_mode)){
        printf("3) Type: socket\n");
        cnt_socket++;
    } else {
        printf("3) unknown file\n");
    }

    printf("4) Size: %ld\n", stat->st_size);

    printf("5) Last accessed: %s\n", ctime(&stat->st_atime));

    printf("6) Last modified: %s\n", ctime(&stat->st_mtime));

    printf("7) Nlink: %ld\n", stat->st_nlink);
    printf("===================================\n\n");
}

void browsing(char* path, int depth){
    if(depth == 5){
        printf("--- There is more but that's enough ---\n\n");
        return;
    }

    DIR* directory = opendir(path);
    struct dirent* entry;

    if(directory == NULL){
        printf("wrong directory\n");
        exit(1);
    }

    char pathWasTaken[100];
    while((entry = readdir(directory)) != NULL){
        strcpy(pathWasTaken, path);
        strcat(pathWasTaken, "/");
        strcat(pathWasTaken, entry->d_name);

        struct stat stat;
        int code;
        code = lstat(pathWasTaken, &stat);
        if(code < 0){
            printf("stat-error\n");
            exit(1);
        }

        if(S_ISDIR(stat.st_mode)){
            if(strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
                continue;

            if(strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0)
                browsing(pathWasTaken, depth + 1);
        }

        print_info(pathWasTaken ,&stat);
    }

    if(depth == 1){
        struct stat stat;
        int code;
        code = lstat(path, &stat);
        if(code < -1){
            printf("stat-error\n");
            exit(1);
        }
        print_info(path ,&stat);
    }
}

int main(int argc, char* argv[]) {
    browsing(argv[1], 1);

    printf("No. files: %d\n", cnt_file);
    printf("No. directories: %d\n", cnt_dir);
    printf("No. char devs: %d\n", cnt_spec_char);
    printf("No. block devs: %d\n", cnt_spec_div);
    printf("No. FIFOs: %d\n", cnt_fifo);
    printf("No. slinks: %d\n", cnt_slink);
    printf("No. sockets: %d\n", cnt_socket);
    return 0;
}
