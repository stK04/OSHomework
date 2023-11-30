#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/shm.h>
#include <sys/sem.h>

#define KEY 1234

int *shm;
int shmid;
int sem_id;

void signal_handler(int sig) {
    if (sig == SIGUSR1) {
        int result = shm[0] + shm[1];
        *shm = result;

        struct sembuf sb = {0, 1, 0};
        semop(sem_id, &sb, 1);

        kill(getppid(), SIGUSR2);
    }
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <shmid> <semid>\n", argv[0]);
        exit(1);
    }

    signal(SIGUSR1, signal_handler);

    shmid = atoi(argv[1]);
    shm = (int*)shmat(shmid, NULL, 0);
    if (shm == (int*)-1) {
        perror("shmat failed");
        exit(1);
    }

    sem_id = atoi(argv[2]);

    while (1) {
        pause();
    }

    return 0;
}
