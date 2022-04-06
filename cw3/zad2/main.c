#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <sys/times.h>
#include <string.h>

FILE *resultFile;

double timeDifference(clock_t t1, clock_t t2){
    return ((double)(t2 - t1) / sysconf(_SC_CLK_TCK));
}

void writeResult(clock_t start, clock_t end, struct tms* t_start, struct tms* t_end){
    printf("\tREAL_TIME: %fl\n", timeDifference(start,end));
    printf("\tUSER_TIME: %fl\n", timeDifference(t_start->tms_utime, t_end->tms_utime));
    printf("\tSYSTEM_TIME: %fl\n\n", timeDifference(t_start->tms_stime, t_end->tms_stime));

    fprintf(resultFile, "\tREAL_TIME: %fl\n", timeDifference(start, end));
    fprintf(resultFile, "\tUSER_TIME: %fl\n", timeDifference(t_start->tms_utime, t_end->tms_utime));
    fprintf(resultFile, "\tSYSTEM_TIME: %fl\n\n", timeDifference(t_start->tms_stime, t_end->tms_stime));
}

int main(int argc, char** argv) {
    resultFile = fopen("./raport", "a");
    struct tms * tms[2];
    clock_t time[2];
    tms[0] = calloc(1, sizeof(struct tms *));
    time[0] = 0;
    tms[1] = calloc(1, sizeof(struct tms *));
    time[1] = 0;
    time[0] = times(tms[0]);

    int status;
    pid_t child_pid = 1;
    double n = atoi(argv[1]);
    double step = 1.0 / n;
    double x = 0.0;
    char point[50];
    char index[50];
    char dash[50];
    snprintf(dash, 50, "%f", step);

    for(int i = 1; i < n + 1; i++) {
        x = x + step;
        if(child_pid != 0) {
            child_pid = fork();
            if(child_pid == 0) {
                snprintf(point, 50, "%f", x - step/2);
                snprintf(index, 50, "%d", i);
                char* const av[]={"./count", point, dash, index, NULL};
                execv("./count", av);
            }
        }
        while(wait(&status) != child_pid)
            continue;
    }

    char buffor[10];
    char file[100];
    double integral = 0.0;
    for(int i = 1; i < n + 1; i++) {
        snprintf(index, 50, "%d", i);

        strcpy(file, "w");
        strcat(file, index);
        strcat(file, ".txt");

        FILE* file_ = fopen(file, "r");
        fread(buffor, 1, 8, file_);
        printf("%s\n", buffor);

        integral = integral + strtod(buffor, NULL);
    }

    fprintf(resultFile, "Liczba procesów: %s\n", argv[1]);
    printf("\n%f\n", integral);
    fprintf(resultFile, "Wynik: %f\n\n", integral);

    time[1] = times(tms[1]);
    writeResult(time[0], time[1],tms[0], tms[1]);
    fclose(resultFile);

    return 0;
}
