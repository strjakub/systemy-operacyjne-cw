#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/times.h>
#include <unistd.h>
#include <ctype.h>

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

void writeToFile(FILE* f_read, FILE* f_write){
    const size_t size = 256;
    char* buffor = malloc(sizeof(char) * size);
    char c;
    int x = 0;
    int mark = 0;

    while(fread(&c, sizeof(char), 1, f_read) == 1){
        if((c == '\n') && (mark == 1)){
            buffor[x] = c;
            fwrite(buffor, sizeof(char), x + 1, f_write);
        }
        if(c == '\n'){
            mark = 0;
            x = 0;
            continue;
        }
        buffor[x] = c;
        if(isspace(buffor[x]) == 0) {
            mark = 1;
        }
        x++;
    }
    free(buffor);
}

int main(int argc, char *argv[]){
    resultFile = fopen("./pomiar_zad_1", "a");
    struct tms * tms[2];
    clock_t time[2];
    tms[0] = calloc(1, sizeof(struct tms *));
    time[0] = 0;
    tms[1] = calloc(1, sizeof(struct tms *));
    time[1] = 0;
    time[0] = times(tms[0]);

    if(argc == 1){
        char in[50];
        char out[50];
        printf("First:\n");
        scanf("%s", in);
        printf("Second:\n");
        scanf("%s",out);

        FILE* one = fopen(in, "r");
        FILE* two = fopen(out, "w");
        writeToFile(one, two);
        fclose(one);
        fclose(two);
    }else if(argc == 2 || argc > 3){
        exit(1);
    }else{
        FILE* one = fopen(argv[1], "r");
        FILE* two = fopen(argv[2], "w");
        writeToFile(one, two);
        fclose(one);
        fclose(two);
    }

    time[1] = times(tms[1]);
    writeResult(time[0], time[1],tms[0], tms[1]);
    fclose(resultFile);
    return 0;
}
