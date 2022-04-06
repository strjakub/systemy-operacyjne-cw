#include <stdio.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>

void ignore(int x) {
    struct sigaction act;
    act.sa_handler = SIG_IGN;
    sigemptyset(&act.sa_mask);
    act.sa_flags = 0;
    sigaction(x, &act, NULL);
}

void handler(int x) {
    printf("\tHandler works:\t%d\n", x);
}

void handle(int x) {
    struct sigaction act;
    act.sa_handler = handler;
    sigemptyset(&act.sa_mask);
    act.sa_flags = 0;
    sigaction(x, &act, NULL);
}

void mask(int x) {
    sigset_t mask_;
    sigemptyset(&mask_);
    sigaddset(&mask_, x);
    sigprocmask(SIG_BLOCK, &mask_, NULL);
}

void pending(int x) {
    sigset_t set;
    if (sigismember(&set, x)) {
        printf("\tSignal %d is pending\n", x);
    }
    else
        printf("\tSignal %d is not pending\n", x);
}

void act(char *command, int x) {
    if (strcmp(command, "ignore") == 0) {
        printf("\n-- IGNORE option --\n");
        ignore(x);
    }
    else if (strcmp(command, "handler") == 0) {
        printf("\n-- HANDLE option --\n");
        handle(x);
    }
    else if (strcmp(command, "mask") == 0 || strcmp(command, "pending") == 0) {
        printf("\n-- MASK/PENDING option --\n");
        mask(x);
    }
    else
        printf("\t\tError - unknown argument\n");
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("\t\tError - invalid number of arguments");
        exit(1);
    }
    int sig = SIGUSR1;

    if (strcmp(argv[0], "exec_test") == 0) {
        printf("\t-- exec start --\n");
        if (strcmp(argv[1], "pending") == 0) {
            pending(sig);
        } else
            raise(sig);
        printf("\t-- exec end --\n");
        exit(0);
    }

    act(argv[1], sig);
    printf("\t-- main start --\n");
    raise(sig);
    if (strcmp(argv[1], "pending") == 0)
        pending(sig);

    #ifdef FORK
        pid_t child_pid = 1;
        if(child_pid != 0)
            child_pid = fork();
        if (child_pid == 0) {
            printf("\t-- fork start --\n");
            if (strcmp(argv[1], "pending") == 0) {
                pending(sig);
            } else
                raise(sig);
            printf("\t-- fork end --\n\n");
            exit(0);
        }
    #endif

    #ifdef EXEC
        pid_t child_pid = 1;
        if(child_pid != 0) {
            child_pid = fork();
            if(child_pid == 0)
                execl(argv[0], "exec_test", argv[1], NULL);
        }
        sleep(1);   //QOL
    #endif

    printf("\t-- main end --\n");

    #ifdef EXEC
        printf("\n");   //QOL
    #endif

    return 0;
}