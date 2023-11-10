#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define NUM_ITERATIONS 10

void *childThread() {
    for (int i = 1; i <= NUM_ITERATIONS; i++) {
        printf("Child Thread. Iteration: %d\n", i);
        sleep(rand() % 3);
    }
    pthread_exit(NULL);
}

int main() {
    srand(time(NULL));

    pthread_t thread;

    if (pthread_create(&thread, NULL, childThread, NULL) != 0) {
        perror("pthread_create");
        return 1;
    }

    for (int i = 1; i <= NUM_ITERATIONS; i++) {
        printf("Main Thread. Iteration: %d\n", i);
        sleep(rand() % 3);
    }

    if (pthread_join(thread, NULL) != 0) {
        perror("pthread_join");
        return 1;
    }

    return 0;
}

