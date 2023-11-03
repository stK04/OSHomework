#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>

#define MAX_BUFFER_SIZE 127

void process_handler() {
    printf("\n\nWait 3 seconds...\n");
    sleep(3);

    system("clear");
    exit(0);
}


int main(int argc, char *argv[]) {
    if (argc > 1 && (strcmp(argv[1], "-h") == 0 || strcmp(argv[1], "--help") == 0)) {
        printf("This is a simple command processor.\n");
        printf("Usage: %s [-b BUFFER_SIZE]\n", argv[0]);
        return 0;
    }

    int buffer_size = MAX_BUFFER_SIZE;

    if (argc > 2 && (strcmp(argv[1], "-b") == 0 || strcmp(argv[1], "--buffer") == 0)) {
        buffer_size = atoi(argv[2]);
        if (buffer_size <= 0) {
            printf("Invalid buffer size. Using default buffer size: %d\n", MAX_BUFFER_SIZE);
            buffer_size = MAX_BUFFER_SIZE;
        }
    }

    char *username = getenv("USER");
    if (username == NULL) {
        printf("Unknown user");
        return 1;
    }

    printf("Welcome, %s!\n", username);

    char *input_buffer = (char *)malloc(buffer_size);
    if (input_buffer == NULL) {
        printf("Error: Failed to allocate memory for the input buffer.\n");
        return 1;
    }

    signal(SIGINT, process_handler);


    while (1) {
        printf("[%s]$ ", username);

        if (fgets(input_buffer, buffer_size, stdin) == NULL) {
            printf("Error reading input.\n");
            break;
        }

        if (strcmp(input_buffer, "stop\n") == 0) {
            printf("Exiting...\n");
            break;
        } else {
            printf("Executing: %s", input_buffer);
            int result = system(input_buffer);
            if (result == -1) {
                printf("Error executing the command.\n");
            }
        }
    }

    free(input_buffer);

    return 0;
}
