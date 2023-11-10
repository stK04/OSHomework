#include <stdio.h>
#include <pthread.h>

#define NUM_THREADS 4

struct ThreadArgs {
    char name[20];
    char str[50];
    int num;
};

void *threadFunction(void *arg) {
    struct ThreadArgs *args = (struct ThreadArgs *)arg;

    for (int i = 1; i <= args->num; i++) {
        printf("Thread %s. %s %d\n", args->name, args->str, i);
    }

    pthread_exit(NULL);
}

int main() {
    pthread_t threads[NUM_THREADS];
    struct ThreadArgs threadArgs[NUM_THREADS];

    for (int i = 0; i < NUM_THREADS; i++) {
        snprintf(threadArgs[i].name, sizeof(threadArgs[i].name), "Thread %d", i + 1);
        snprintf(threadArgs[i].str, sizeof(threadArgs[i].str), "Str");
        threadArgs[i].num = 5;
    }

    for (int i = 0; i < NUM_THREADS; i++) {
        if (pthread_create(&threads[i], NULL, threadFunction, &threadArgs[i]) != 0) {
            perror("pthread_create");
            return 1;
        }
    }

    for (int i = 0; i < NUM_THREADS; i++) {
        if (pthread_join(threads[i], NULL) != 0) {
            perror("pthread_join");
            return 1;
        }
    }

    return 0;
}
