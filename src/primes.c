// Program primes.c by Alan K Stewart
// Calculates prime numbers using the Sieve of Eratosthenes

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <stdbool.h>
#include <pthread.h>
#include <errno.h>

typedef struct {
    int limit;
    _Bool *composite;
} sieve_args;

void *eratosthenesSieve(void *arg);

int main(int argc, char** argv) {

    int limit, number;
    _Bool *composite;
    sieve_args sieve;
    pthread_t thread;

    if (argc == 1) {
        limit = 100;
    } else if (argc > 2 || atoi(argv[1]) < 2) {
        fprintf(stderr, "Must be 2 or greater\n");
        exit(EXIT_FAILURE);
    } else {
        limit = atoi(argv[1]);
    }

    if ((composite = malloc((limit + 1) * sizeof(_Bool))) == NULL) {
        perror("Failed to allocate memory");
        exit(EXIT_FAILURE);
    }
    sieve.limit = limit;
    sieve.composite = composite;

    pthread_create(&thread, NULL, eratosthenesSieve, &sieve);

    printf("Enter a number between 2 and %d: ", limit);
    scanf("%d", &number);

    pthread_join(thread, NULL);

    if (number < 2 || number > limit) {
        fprintf(stderr, "Number must be between 2 and %d\n", limit);
        exit(EXIT_FAILURE);
    }

    printf(composite[number] ? "%d is not prime\n" : "%d is prime\n", number);

#ifdef DEBUG
    printf("\n");
    for (int i = 2; i <= limit; i++) {
        if (!composite[i]) {
            printf("%d ", i);
        }
    }
    printf("\n");
#endif

    free(composite);
    return EXIT_SUCCESS;
}

void *eratosthenesSieve(void *arg) {

    sieve_args* sieve = (sieve_args*) arg;
    int limit = sieve->limit;
    _Bool *composite = sieve->composite;

    int limitSqrt = (int) floor(sqrt((double) limit));
    for (int i = 2; i <= limitSqrt; i++) {
        if (!composite[i]) {
            for (int j = i * i; j <= limit; j += i) {
                composite[j] = true;
            }
        }
    }

   pthread_exit(0);
}
