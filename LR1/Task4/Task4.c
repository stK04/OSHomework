#include <stdio.h>
#include <pthread.h>

#define NUM_THREADS 2
#define NUM_CATALAN 12
#define NUM_PRIMES 12

unsigned long long catalan_numbers[NUM_CATALAN];
int prime_numbers[NUM_PRIMES];

unsigned long long calculateCatalan(int n) {
    if (n <= 1) return 1;

    unsigned long long res = 0;
    for (int i = 0; i < n; i++) {
        res += calculateCatalan(i) * calculateCatalan(n - 1 - i);
    }

    return res;
}

int isPrime(int num) {
    if (num <= 1) return 0;
    if (num <= 3) return 1;

    if (num % 2 == 0 || num % 3 == 0) return 0;

    for (int i = 5; i * i <= num; i += 6) {
        if (num % i == 0 || num % (i + 2) == 0) return 0;
    }

    return 1;
}

void *catalanThread(void *arg) {
    for (int i = 0; i < NUM_CATALAN; i++) {
        catalan_numbers[i] = calculateCatalan(i);
    }

    pthread_exit(NULL);
}

void *primeThread(void *arg) {
    int count = 0;
    for (int i = 2; count < NUM_PRIMES; i++) {
        if (isPrime(i)) {
            prime_numbers[count] = i;
            count++;
        }
    }

    pthread_exit(NULL);
}

int main() {
    pthread_t threads[NUM_THREADS];

    if (pthread_create(&threads[0], NULL, catalanThread, NULL) != 0) {
        perror("pthread_create");
        return 1;
    }

    if (pthread_create(&threads[1], NULL, primeThread, NULL) != 0) {
        perror("pthread_create");
        return 1;
    }

    for (int i = 0; i < NUM_THREADS; i++) {
        if (pthread_join(threads[i], NULL) != 0) {
            perror("pthread_join");
            return 1;
        }
    }

    printf("Catalan Numbers: ");
    for (int i = 0; i < NUM_CATALAN; i++) {
        printf("%llu ", catalan_numbers[i]);
    }
    printf("\n");

    printf("Prime Numbers: ");
    for (int i = 0; i < NUM_PRIMES; i++) {
        printf("%d ", prime_numbers[i]);
    }
    printf("\n");

    return 0;
}
