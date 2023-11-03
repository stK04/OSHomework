#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAX_FILENAME_LENGTH 256

void create_and_write_file(int number, char *filename) {
    char file_name[MAX_FILENAME_LENGTH];
    snprintf(file_name, sizeof(file_name), "%s%d.txt", filename, number);

    FILE *file = fopen(file_name, "w");
    if (file == NULL) {
        perror("Error opening file");
        exit(1);
    }
    for (int i = 0; i < number; i++) {
        int random_number = rand() % 2;
        fprintf(file, "%d\n", random_number);
    }
    fclose(file);
}

int main(int argc, char *argv[]) {
    int number = 0;
    char *filename = "default";

    int opt;
    while ((opt = getopt(argc, argv, "f:n:")) != -1) {
        switch (opt) {
            case 'f':
                filename = optarg;
                break;
            case 'n':
                number = atoi(optarg);
                break;
            default:
                fprintf(stderr, "Usage: %s [-f filename] [-n number]\n", argv[0]);
                exit(1);
        }
    }

    if (number <= 0) {
        printf("Invalid number. Please specify a positive integer using -n option.\n");
        exit(1);
    }

    printf("\nnumber: %d\n", number);

    for (int i = 1; i <= number; i++) {
        pid_t pid = fork();

        if (pid < 0) {
            perror("Fork error");
            exit(1);
        } else if (pid == 0) { // child
            create_and_write_file(i, filename);
            exit(0);
        } else { // parent
            int status;
            waitpid(pid, &status, 0);
        }
    }

    printf("All child processes have finished.\n");

    return 0;
}
