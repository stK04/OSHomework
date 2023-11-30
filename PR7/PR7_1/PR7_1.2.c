#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/shm.h>

int *shm;
int shmid;

void signal_handler(int sig) {
    if (sig == SIGUSR1) {
        int result = shm[0] + shm[1];
        *shm = result;
        kill(getppid(), SIGUSR2);
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <shmid>\n", argv[0]);
        exit(1);
    }

    signal(SIGUSR1, signal_handler);

    shmid = atoi(argv[1]);
    shm = (int*) shmat(shmid, NULL, 0);
    if (shm == (int*) -1) {
        perror("shmat failed");
        exit(1);
    }

    while (1) {
        pause();
    }

    return 0;
}
