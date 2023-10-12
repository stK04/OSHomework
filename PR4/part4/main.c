#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pwd.h>

int main() {
    uid_t uid = getuid();

    struct passwd* user = getpwuid(uid);
    if (user == NULL) {
        printf("Failed to get information about the user.\n");
        return 1;
    }

    printf("Username: %s\n", user->pw_name);
    printf("Home directory: %s\n", user->pw_dir);
    printf("Path to the command interpreter: %s\n", user->pw_shell);

    struct passwd* root = getpwnam("root");
    if (root == NULL) {
        printf("Failed to get information about the user root.\n");
        return 1;
    }

    printf("Username root: %s\n", root->pw_name);
    printf("Home directory root: %s\n", root->pw_dir);
    printf("Path to the command interpreter root: %s\n", root->pw_shell);

    return 0;
}
