#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

int counter = 0;
int pid = 0;
int flag = 0;
int mode = 0;

void handler1(int x, siginfo_t *info, void *secret){
    counter++;
    pid = info->si_pid;

    if(mode == 1)
        kill(pid, 10);
    else if(mode == 2) {
        union sigval val;
        val.sival_int = counter;
        sigqueue(pid, 10, val);
    }else if(mode == 3)
        kill(pid, SIGRTMIN + 1);
}

void handler2(int x) {
    if(mode == 1) {
        kill(pid, 12);
    }else if(mode == 2){
        kill(pid, 12);
    }
    else if(mode == 3){
        kill(pid, SIGRTMIN+2);
    }
    flag = 1;
}

int main(int argc, char* argv[]){
    printf("PID:\t%d\n", getpid());
    fflush(stdout);
    mode = atoi(argv[1]);

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

    struct sigaction act3;
    act3.sa_flags = SA_SIGINFO;
    act3.sa_sigaction = &handler1;
    if (sigaction(SIGRTMIN+1, &act3, NULL) == -1) {
        perror("sigaction");
    }

    struct sigaction act4;
    act4.sa_flags = 0;
    act4.sa_handler = handler2;
    if (sigaction(SIGRTMIN+2, &act4, NULL) == -1) {
        perror("sigaction");
    }

    while(flag == 0);

    return 0;
}
