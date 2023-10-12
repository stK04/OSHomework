#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern char **environ;

void display_environment() {
    char **env = environ;
    while (*env) {
        printf("%s\n", *env);
        env++;
    }
}

void display_help() {
    printf("Help:\n");
    printf("-h or --help: Display this help message\n");
    printf("-i or --info <variable>: Display information about a variable\n");
    printf("-s or --set <variable=value>: Set the value of a variable\n");
    printf("-a or --assign <variable> --value <value>: Assign a new value to a variable\n");
    printf("-d or --del <variable>: Delete a variable from the environment\n");
    printf("-c or --clear: Clear the entire environment\n");
}

void display_variable(const char *variable_name) {
    char *value = getenv(variable_name);
    if (value) {
        printf("%s=%s\n", variable_name, value);
    } else {
        printf("Variable %s is not present in the environment.\n", variable_name);
    }
}

void set_variable(const char *variable_name, const char *value) {
    if (setenv(variable_name, value, 1) == 0) {
        printf("%s=%s\n", variable_name, value);
    } else {
        perror("Error setting the variable");
    }
}

void assign_variable(const char *variable_name, const char *value) {
    if (setenv(variable_name, value, 1) == 0) {
        printf("%s=%s\n", variable_name, value);
    } else {
        perror("Error assigning a value to the variable");
    }
}

void delete_variable(const char *variable_name) {
    if (unsetenv(variable_name) == 0) {
        printf("Variable %s has been removed from the environment\n", variable_name);
    } else {
        perror("Error deleting the variable");
    }
}

void clear_environment() {
    while (*environ) {
        unsetenv(*environ);
        environ++;
    }
}

int main(int argc, char *argv[]) {
    if (argc == 1) {
        display_environment();
    } else if (argc == 2 && (strcmp(argv[1], "-h") == 0 || strcmp(argv[1], "--help") == 0)) {
        display_help();
    } else if ((strcmp(argv[1], "-i") == 0 || strcmp(argv[1], "--info") == 0) && argc == 3) {
        display_variable(argv[2]);
    } else if ((strcmp(argv[1], "-s") == 0 || strcmp(argv[1], "--set") == 0) && argc == 4) {
        set_variable(argv[2], argv[3]);
    } else if ((strcmp(argv[1], "-a") == 0 || strcmp(argv[1], "--assign") == 0) && argc == 4) {
        assign_variable(argv[2], argv[3]);
    } else if ((strcmp(argv[1], "-d") == 0 || strcmp(argv[1], "--del") == 0) && argc == 3) {
        delete_variable(argv[2]);
    } else if ((strcmp(argv[1], "-c") == 0 || strcmp(argv[1], "--clear") == 0) && argc == 2) {
        clear_environment();
    } else {
        printf("Invalid options or parameters. Use -h or --help for help.\n");
    }

    return 0;
}
