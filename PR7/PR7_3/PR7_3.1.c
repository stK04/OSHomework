#include <stdio.h>
#include <signal.h>
#include <unistd.h>

void sig_handler(int signum) {
    switch (signum) {
        case SIGINT:
            printf("Caught SIGINT signal\n");
            break;
        case SIGTERM:
            printf("Caught SIGTERM signal\n");
            break;
        case SIGUSR1:
            printf("Caught SIGUSR1 signal. Terminating the program.\n");
            _exit(0);
            break;
        default:
            break;
    }
}

int main() {
    signal(SIGINT, sig_handler);
    signal(SIGTERM, sig_handler);
    signal(SIGUSR1, sig_handler);
    signal(SIGPROF, SIG_DFL);
    signal(SIGHUP, SIG_IGN);

    printf("Process ID: %d\n", getpid());

    while (1) {
        pause();
    }

    return 0;
}