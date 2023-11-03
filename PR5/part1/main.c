#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s \"command1; command2; ...\"\n", argv[0]);
        return 1;
    }

    char *commands = argv[1];

    char *token = strtok(commands, ";");
    while (token != NULL) {
        int return_code = system(token);

        printf("Command: %s\n", token);
        printf("Exit Code: %d\n", return_code);

        token = strtok(NULL, ";");
    }

    return 0;
}
