#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv) {

    if (argc < 3) {
        printf("Usage: %s <environment variable name> <environment variable value>\n", argv[0]);
        return 1;
    }

    int result = setenv(argv[1], argv[2], 1);
    if (result != 0) {
        printf("Failed to set environment variable.\n");
        return 1;
    }

    char* value = getenv(argv[1]);
    if (value == NULL) {
        printf("Environment variable \"%s\" does not exist.\n", argv[1]);
        return 1;
    }

    printf("Environment variable \"%s\": %s\n", argv[1], value);

    return 0;
}
