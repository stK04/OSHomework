#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>

void alarm_handler(int signum) {
    if (signum == SIGALRM) {
        printf("Alarm: Time to wake up!\n");
    }
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Usage: %s <seconds> <message>\n", argv[0]);
        return 1;
    }

    int seconds = atoi(argv[1]);
    char *message = argv[2];

    signal(SIGALRM, alarm_handler);

    pid_t pid = fork();

    if (pid < 0) {
        perror("Fork failed");
        return 1;
    } else if (pid == 0) {
        // Child process
        sleep(seconds);
        kill(getppid(), SIGALRM);
        exit(0);
    } else {
        // Parent process
        printf("Alarm set for %d seconds...\n", seconds);
        printf("Message: %s\n", message);
        pause(); // Wait for SIGALRM
        printf("Exiting...\n");
    }

    return 0;
}
