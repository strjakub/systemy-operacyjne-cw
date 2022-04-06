#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>

int main(int argc, char** argv) {

    if(atoi(argv[3]) == 0) {
        printf("--LIMIT GŁĘBOKOŚCI--\n");
        return 0;
    }

    int status;
    pid_t child_pid = 1;
    int n = atoi(argv[3]);
    char depth[50];
    snprintf(depth, 50, "%d", n - 1);

    DIR* directory = opendir(argv[1]);
    struct dirent* entry;

    if(directory == NULL){
        printf("wrong directory\n");
        exit(1);
    }

    char pathWasTaken[100];
    while((entry = readdir(directory)) != NULL){
        strcpy(pathWasTaken, argv[1]);
        strcat(pathWasTaken, "/");
        strcat(pathWasTaken, entry->d_name);

        char command[100] = "";
        struct stat stat;
        int code;
        code = lstat(pathWasTaken, &stat);
        if(code < 0){
            printf("stat-error\n");
            exit(1);
        }

        if(S_ISREG(stat.st_mode)){
            strcpy(command, "grep ");
            strcat(command, argv[2]);
            strcat(command, " ");
            strcat(command, pathWasTaken);

            if(system(command) == 0)
                printf("\tZnaleziono dopasowanie w pliku:\n\t%s\n\tDokonał tego proces:"
                       "\n\t-- %d --\n\tGłębokość: %d\n", pathWasTaken, (int) getpid(), n);
        }

        if(S_ISDIR(stat.st_mode)){
            if(strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
                continue;

            if(strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0){
                if(child_pid != 0) {
                    child_pid = fork();
                    if(child_pid == 0) {
                        char* const av[]={"./main", pathWasTaken, argv[2], depth,  NULL};
                        execv("./main", av);
                    }
                }
                while(wait(&status) != child_pid)
                    continue;
            }
        }
    }

    if(child_pid != 0)
        printf("Zakończył szukanie: %d\n", (int) getpid());

    return 0;
}