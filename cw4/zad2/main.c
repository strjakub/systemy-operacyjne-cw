#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>

int counter = 0;

void handler_info(int sig, siginfo_t *info, void *secret){
    printf("PID:\t\t%d\n", info->si_pid);
    printf("SIGNO:\t\t%d\n", info->si_signo);
    printf("SIGCODE:\t%d\n\n", info->si_code);
}

void handler_reset(int x){
    printf("Handler dla SIGTERM zgłasza się, bez odbioru\n");
}

void handler_loop(int x){
    if(counter < 3) {
        counter++;
        printf("handler - start\n");
        sleep(2);
        printf("new SIGTERM\n");
        raise(2);
        sleep(2);
        printf("handler - stop\n");
    }
}

int main(int argc, char* argv[]) {
    int n = atoi(argv[1]);

    if(n == 1) {
        printf("\n\t-- SA_SIGINFO --\t\n\n");
        sleep(2);
        struct sigaction act1;
        act1.sa_flags = SA_SIGINFO;
        act1.sa_sigaction = &handler_info;
        if (sigaction(10, &act1, NULL) == -1) {
            perror("sigaction");
        }
        if (sigaction(11, &act1, NULL) == -1) {
            perror("sigaction");
        }
        if (sigaction(12, &act1, NULL) == -1) {
            perror("sigaction");
        }
        raise(10);
        sleep(1);
        raise(11);
        sleep(1);
        raise(12);
    }

    if(n == 2) {
        printf("\n\t-- SA_RESETHAND --\t\n\nHandler staje się jednorazowy, wykona się dla pierwszego\nSIGTERM'a, ale dla drugiego już nie.\n\n");
        struct sigaction act2;
        act2.sa_flags = SA_RESETHAND;
        act2.sa_handler = handler_reset;
        if (sigaction(15, &act2, NULL) == -1) {
            perror("sigaction");
        }
        sleep(6);
        raise(15);
        sleep(3);
        raise(15);
    }

    if(n == 3) {
        printf("\n\t-- SA_NODEFER --\t\n\nmożemy złapać sygnał kiedy wykonuje się Jego handler\n(handlery mogą się stackować)\n\n");
        sleep(5);
        struct sigaction act3;
        act3.sa_handler = handler_loop;
        act3.sa_flags = 0;
        sigemptyset(&act3.sa_mask);
        sigaction(2, &act3, NULL);
        printf("Without NODEFER\n");
        raise(2);
        act3.sa_handler = handler_loop;
        act3.sa_flags = SA_NODEFER;
        sigemptyset(&act3.sa_mask);
        sigaction(2, &act3, NULL);
        printf("\nWith NODEFER\n");
        counter = 0;
        raise(2);
    }

    return 0;
}
