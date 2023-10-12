#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv) {

    if (argc < 2) {
        int result = clearenv();
        if (result != 0) {
            printf("Failed to clear environment.\n");
            return 1;
        }
    } else {
        int result = unsetenv(argv[1]);
        if (result != 0) {
            printf("Failed to remove environment variable \"%s\".\n", argv[1]);
            return 1;
        }
    }

    extern char **environ;
    char **env = environ;
    while (*env) {
        printf("%s\n", *env);
        env++;
    }

    return 0;
}

