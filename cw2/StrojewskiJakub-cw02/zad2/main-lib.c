#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/times.h>
#include <unistd.h>

FILE *resultFile;

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

void writeToFile(FILE* f_read, char letter, FILE* result){
    const size_t size = 256;
    char* buffor = malloc(sizeof(char) * size);
    char c;
    int x = 0;
    int mark;
    int counter = 0;
    int line_counter = 0;

    while(fread(&c, sizeof(char), 1, f_read) == 1){
        if((c == '\n') && (mark == 1)){
            line_counter++;
        }
        if(c == '\n'){
            mark = 0;
            x = 0;
            continue;
        }
        buffor[x] = c;
        if(buffor[x] == letter) {
            counter++;
            mark = 1;
        }
        x++;
    }

    printf("Letters: %d\nLines_withLetters: %d\n", counter, line_counter);
    fprintf(result, "Letters: %d\nLines_withLetters: %d\n", counter, line_counter);
    free(buffor);
}

int main(int argc, char *argv[]){
    resultFile = fopen("./pomiar_zad_2", "a");
    struct tms * tms[2];
    clock_t time[2];
    tms[0] = calloc(1, sizeof(struct tms *));
    time[0] = 0;
    tms[1] = calloc(1, sizeof(struct tms *));
    time[1] = 0;
    time[0] = times(tms[0]);

    FILE* one = fopen(argv[2], "r");
    writeToFile(one, *argv[1], resultFile);
    fclose(one);


    time[1] = times(tms[1]);
    writeResult(time[0], time[1],tms[0], tms[1]);
    fclose(resultFile);
    return 0;
}
