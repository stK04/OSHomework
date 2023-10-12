#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {

    printf("\nAll environmental variables:\n");

    extern char **environ;
    char **env = environ;

    while (*env) {
        printf("%s\n", *env);
        env++;
    }

    printf("\nYour environmental variable:\n");

    if (argc != 2) {
        printf("Usage: %s <environment_variable_name>\n", argv[0]);
        return 1;
    }

    const char *variable_name = argv[1];
    char *variable_value = getenv(variable_name);

    if (variable_value == NULL) {
        printf("Variable '%s' not exist in the environment.\n", variable_name);
    } else {
        printf("Env variable %s=%s\n", variable_name, variable_value);
    }

    return 0;
}