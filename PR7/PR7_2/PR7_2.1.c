#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/shm.h>
#include <sys/wait.h>
#include <signal.h>
#include <sys/sem.h>

#define KEY 1234

int shmid;
int *shm;
pid_t child_pid;
int sem_id;

union semun {
    int val;
    struct semid_ds *buf;
    unsigned short *array;
};

void signal_handler(int sig) {
    if (sig == SIGUSR2) {
        printf("Received sum from child: %d\n", *shm);
    }
}

void remove_resources() {
    shmdt(shm);
    shmctl(shmid, IPC_RMID, NULL);
    semctl(sem_id, 0, IPC_RMID);
    printf("Resources removed\n");
}

int main() {
    signal(SIGUSR2, signal_handler);

    sem_id = semget(KEY, 1, 0666 | IPC_CREAT);
    if (sem_id == -1) {
        perror("semget failed");
        exit(1);
    }

    union semun arg;
    arg.val = 1;
    if (semctl(sem_id, 0, SETVAL, arg) == -1) {
        perror("semctl failed");
        exit(1);
    }

    shmid = shmget(IPC_PRIVATE, sizeof(int), 0666 | IPC_CREAT);
    if (shmid == -1) {
        perror("shmget failed");
        exit(1);
    }

    shm = (int*)shmat(shmid, NULL, 0);
    if (shm == (int*)-1) {
        perror("shmat failed");
        exit(1);
    }

    child_pid = fork();
    if (child_pid < 0) {
        perror("fork failed");
        exit(1);
    } else if (child_pid == 0) {
        char shmid_str[10];
        sprintf(shmid_str, "%d", shmid);
        char sem_id_str[10];
        sprintf(sem_id_str, "%d", sem_id);
        execl("child_program", "child", shmid_str, sem_id_str, NULL);
        perror("execl failed");
        exit(1);
    } else {
        int data1, data2;
        do {
            printf("Enter two integers (Ctrl + C to exit): ");
            scanf("%d %d", &data1, &data2);

            if (data1 != -1 && data2 != -1) {
                shm[0] = data1;
                shm[1] = data2;

                struct sembuf sb = {0, -1, 0}; // Заборона доступу
                semop(sem_id, &sb, 1);

                kill(child_pid, SIGUSR1);

                pause();
            }
        } while (data1 != -1 && data2 != -1);

        wait(NULL);
        remove_resources();
        printf("Parent exiting\n");
    }

    return 0;
}
