#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

int counter = 0;
int actualCounter = 0;
int flag = 0;
int mode = 0;
int max = 0;

void handler1(int xnt, siginfo_t *info, void *secret){
    counter++;
    if(mode == 2 && max < info->si_value.sival_int){
        max = info->si_value.sival_int;
    }
}

void handler2(int x){
    printf("Expected:\t\t%d\n", actualCounter);
    printf("Actual:\t\t\t%d\n", counter);
    if(mode == 2){
        printf("Max received signal No:\t%d\n", max);
    }
    flag = 1;
}

int main(int argc, char* argv[]) {
    int n = atoi(argv[2]);
    int pid = atoi(argv[1]);
    mode = atoi(argv[3]);

    if(mode == 3){
        struct sigaction act1;
        act1.sa_flags = SA_SIGINFO;
        act1.sa_sigaction = &handler1;
        if (sigaction(SIGRTMIN+1, &act1, NULL) == -1) {
            perror("sigaction");
        }

        struct sigaction act2;
        act2.sa_flags = 0;
        act2.sa_handler = handler2;
        if (sigaction(SIGRTMIN+2, &act2, NULL) == -1) {
            perror("sigaction");
        }

        for (int i = 0; i < n; i++) {
            actualCounter++;
            kill(pid, SIGRTMIN+1);
        }
        kill(pid, SIGRTMIN+2);

    }else {
        struct sigaction act1;
        act1.sa_flags = SA_SIGINFO;
        act1.sa_sigaction = &handler1;
        if (sigaction(10, &act1, NULL) == -1) {
            perror("sigaction");
        }

        struct sigaction act2;
        act2.sa_flags = 0;
        act2.sa_handler = handler2;
        if (sigaction(12, &act2, NULL) == -1) {
            perror("sigaction");
        }

        if (mode == 1) {
            for (int i = 0; i < n; i++) {
                actualCounter++;
                kill(pid, 10);
            }
            kill(pid, 12);
        } else if (mode == 2) {
            union sigval x;
            for (int i = 0; i < n; i++) {
                x.sival_int = i + 1;
                actualCounter++;
                sigqueue(pid, 10, x);
            }
            kill(pid, 12);
        }
    }

    while(flag == 0);

    return 0;
}
