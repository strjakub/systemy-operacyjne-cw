#include <stdlib.h>
#include "mylib.h"
#include <stdio.h>
#include <unistd.h>
#include <sys/times.h>

FILE * resultFile;

void error(char * msg){
    printf("%s", msg);
    fprintf(resultFile, "%s", msg);
    exit(0);
}

const char *get_filename_ext(const char *filename) {
    const char *dot = strrchr(filename, '.');
    if(!dot || dot == filename) return "";
    return dot + 1;
}


double timeDifference(clock_t t1, clock_t t2){
    return ((double)(t2 - t1) / sysconf(_SC_CLK_TCK));
}

void writeResult(clock_t start, clock_t end, struct tms* t_start, struct tms* t_end){
    printf("\tREAL_TIME: %fl\n", timeDifference(start,end));
    printf("\tUSER_TIME: %fl\n", timeDifference(t_start->tms_utime, t_end->tms_utime));
    printf("\tSYSTEM_TIME: %fl\n", timeDifference(t_start->tms_stime, t_end->tms_stime));

    fprintf(resultFile, "\tREAL_TIME: %fl\n", timeDifference(start, end));
    fprintf(resultFile, "\tUSER_TIME: %fl\n", timeDifference(t_start->tms_utime, t_end->tms_utime));
    fprintf(resultFile, "\tSYSTEM_TIME: %fl\n", timeDifference(t_start->tms_stime, t_end->tms_stime));
}

int main(int argc, char **argv) {
    int i;
    int size = argc;
    resultFile = fopen("./raport3b.txt", "a");
    struct tms * tms[size];
    clock_t time[size];
    for(i = 0; i < size; i++){
        tms[i] = calloc(1, sizeof(struct tms *));
        time[i] = 0;
    }

    if(argc < 2)
        error("Bad argument");

    int current = 0;
    struct ArrayOfBlocks myBlocks;
    for(i = 2; i < argc; ++i){
        time[current] = times(tms[current]);
        current += 1;

        if(strcmp(argv[i], "create_table") == 0){
            if(!isNumber(argv[i+1]))
                error("Bad argument");

            printf("Create table size %s:\n", argv[i+1]);
            fprintf(resultFile, "Create table size %s\n", argv[i+1]);

            myBlocks = createArrayOfBlocks(atoi(argv[i+1]));
            i++;
        }
        else if(strcmp(argv[i], "wc_files") == 0){
            tmp_create();
            while(i + 1 < argc && strcmp(get_filename_ext(argv[i + 1]), "txt") == 0){
                if(myBlocks.size == myBlocks.max_size)
                    error("No memory");
                int x = count(myBlocks, argv[i + 1]);

                printf("Written to block %d\n", x);
                fprintf(resultFile, "Written to block %d\n", x);

                myBlocks.size = myBlocks.size + 1;
                i++;
            }
            tmp_remove();
        }
        else if(strcmp(argv[i], "remove_block") == 0){
            if(!isNumber(argv[i+1]))
                error("Bad argument");

            printf("Remove block %s:\n", argv[i+1]);
            fprintf(resultFile, "Remove block %s\n", argv[i+1]);

            removeBlock(myBlocks, atoi(argv[i+1]));
            myBlocks.size = myBlocks.size - 1;
            i++;
        }
        else
            error("Bad argument");
        time[current] = times(tms[current]);
        writeResult(time[current-1], time[current],tms[current-1], tms[current]);
        current += 1;
    }
    fprintf(resultFile, "==============================\n \n");
    return 0;
}
