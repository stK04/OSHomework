#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/utsname.h>

int main() {
    char hostname[_SC_HOST_NAME_MAX];
    int result = gethostname(hostname, sizeof(hostname));
    if (result != 0) {
        printf("Failed to get the hostname of the computer.\n");
        return 1;
    }

    struct utsname name;
    result = uname(&name);
    if (result != 0) {
        printf("Failed to get information about the computer.\n");
        return 1;
    }

    printf("Hostname of the computer: %s\n", hostname);
    printf("Operating system name: %s\n", name.sysname);
    printf("Kernel version: %s\n", name.release);
    printf("Architecture: %s\n", name.machine);
    printf("Kernel build number: %s\n", name.version);

    return 0;
}

