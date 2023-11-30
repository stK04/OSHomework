#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/shm.h>
#include <sys/wait.h>
#include <signal.h>

int shmid;
int *shm;
pid_t child_pid;

void signal_handler(int sig) {
    if (sig == SIGUSR2) {
        printf("Received sum from child: %d\n", *shm);
    }
}

int main() {
    signal(SIGUSR2, signal_handler);

    shmid = shmget(IPC_PRIVATE, sizeof(int), 0666 | IPC_CREAT);
    if (shmid == -1) {
        perror("shmget failed");
        exit(1);
    }

    shm = (int*) shmat(shmid, NULL, 0);
    if (shm == (int*) -1) {
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
        execl("child_program", "child", shmid_str, NULL);
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
                kill(child_pid, SIGUSR1);

                pause();
            }
        } while (data1 != -1 && data2 != -1);
        
        wait(NULL);
        shmdt(shm);
        shmctl(shmid, IPC_RMID, NULL);
        printf("Parent exiting\n");
    }

    return 0;
}
