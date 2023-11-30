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
    struct sigaction sa;
    sa.sa_handler = sig_handler;
    sa.sa_flags = 0;
    sigemptyset(&sa.sa_mask);

    sigaction(SIGINT, &sa, NULL);
    sigaction(SIGTERM, &sa, NULL);
    sigaction(SIGUSR1, &sa, NULL);
    signal(SIGPROF, SIG_DFL);
    signal(SIGHUP, SIG_IGN);

    printf("Process ID: %d\n", getpid());

    while (1) {
        pause();
    }

    return 0;
}
