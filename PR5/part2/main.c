#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <sys/wait.h>


void process_handler(int signum) {
    sleep(2);

    printf("Handler %d: Process terminated.\n", signum);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <num_handlers>\n", argv[0]);
        return 1;
    }

    int num_handlers = atoi(argv[1]);

    if (num_handlers < 1) {
        printf("Please provide a valid number of handlers greater than 0.\n");
        return 1;
    }

    for (int i = 0; i < num_handlers; i++) {
        if(signal(SIGINT, process_handler) == SIG_ERR) {
            printf("Error making child\n");
            return 1;
        }
    }

    printf("Registered %d process handlers. Waiting for child processes...\n", num_handlers);


    while(1) {
        pause();
    }

    return 0;
}
