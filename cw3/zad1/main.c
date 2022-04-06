#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char** argv) {
    pid_t child_pid = 1;

    for(int i = 0; i < atoi(argv[1]); i++) {
        if(child_pid != 0)
            child_pid = fork();
    }

    if (child_pid != 0)
        printf("Rodzic: %d\n", (int) getpid());
    else
        printf("Dziecko: %d\n", (int) getpid());

    return 0;
}
