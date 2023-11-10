#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

#define NUM_CHILD_THREADS 2

void *stringThread(void *arg) {
    char *str = (char *)arg;
    int num_iterations = 10;

    for (int i = 1; i <= num_iterations; i++) {
        printf("%s: Iteration %d\n", str, i);
    }

    pthread_exit(NULL);
}

void *randomNumberThread(void *arg) {
    int target_number = *((int *)arg);
    int num_iterations = 20;

    for (int i = 1; i <= num_iterations; i++) {
        int generated_number = rand() % 100;
        printf("Random Number: Iteration %d, Generated: %d\n", i, generated_number);

        if (generated_number == target_number) {
            printf("Random Number Thread: Found the target number %d, exiting.\n", target_number);
            pthread_exit(NULL);
        }
    }

    pthread_exit(NULL);
}

int main() {
    srand(time(NULL));

    pthread_t threads[NUM_CHILD_THREADS];
    char *str = "String Thread";
    int target_number = 42;

    if (pthread_create(&threads[0], NULL, stringThread, str) != 0) {
        perror("pthread_create");
        return 1;
    }

    if (pthread_create(&threads[1], NULL, randomNumberThread, &target_number) != 0) {
        perror("pthread_create");
        return 1;
    }

    for (int i = 0; i < NUM_CHILD_THREADS; i++) {
        if (pthread_join(threads[i], NULL) != 0) {
            perror("pthread_join");
            return 1;
        }
    }

    printf("Main Thread: All child threads have finished.\n");

    return 0;
}
