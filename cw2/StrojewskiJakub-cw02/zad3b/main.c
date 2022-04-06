#define _XOPEN_SOURCE 500
#include <ftw.h>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <sys/stat.h>
#include <time.h>

int cnt_file = 0;
int cnt_dir = 0;
int cnt_spec_char = 0;
int cnt_spec_div = 0;
int cnt_fifo = 0;
int cnt_slink = 0;
int cnt_socket = 0;

int print_info(const char* filename, const struct stat *stat, int i, struct FTW *pFTW){
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
    return 0;
}

int main(int argc, char* argv[]) {
    nftw(argv[1], print_info, 3, FTW_PHYS | FTW_DEPTH);

    printf("No. files: %d\n", cnt_file);
    printf("No. directories: %d\n", cnt_dir);
    printf("No. char devs: %d\n", cnt_spec_char);
    printf("No. block devs: %d\n", cnt_spec_div);
    printf("No. FIFOs: %d\n", cnt_fifo);
    printf("No. slinks: %d\n", cnt_slink);
    printf("No. sockets: %d\n", cnt_socket);
    return 0;
}

//FTW_PHYS
//If set, nftw() shall perform a physical walk
//and shall not follow symbolic links.
//FTW_DEPTH
//If set, nftw() shall report all files in a directory
//before reporting the directory itself. If clear,
//nftw() shall report any directory before reporting
//the files in that directory.