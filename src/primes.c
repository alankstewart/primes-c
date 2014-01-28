// Program primes.c by Alan K Stewart
// Calculates prime numbers using the Sieve of Eratosthenes

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <stdbool.h>
#include <pthread.h>
#include <errno.h>

void *eratosthenesSieve(int *upperBound);

int main(int argc, char** argv) {
    int upperBound, number;

    if (argc == 1) {
        upperBound = 100;
    } else if (argc > 2 || atoi(argv[1]) < 2) {
        printf("Usage: primes <number greater than 1>\n");
        exit(EXIT_FAILURE);
    } else {
        upperBound = atoi(argv[1]);
    }

    pthread_t thread;
    _Bool *composite;
    pthread_create(&thread, NULL, (void*(*)(void*)) eratosthenesSieve, &upperBound);
    printf("Enter a number between 2 and %d: ", upperBound);
    scanf("%d", &number);
    pthread_join(thread, (void**) &composite);

#ifdef DEBUG
    for (int i = 2; i <= upperBound; i++) {
        if (!composite[i]) {
            printf("%d ", i);
        }
    }
    printf("\n");
#endif

    if (number < 2 || number > upperBound) {
        fprintf(stderr, "Number must be between 2 and %d\n", upperBound);
        exit(EXIT_FAILURE);
    }

    if (composite[number] == true) {
        printf("%d is not prime\n", number);
    } else {
        printf("%d is prime\n", number);
    }

    free(composite);
    return EXIT_SUCCESS;
}

void *eratosthenesSieve(int *upperBound) {
    _Bool *composite;

    if ((composite = malloc((*upperBound + 1) * sizeof(_Bool))) == NULL) {
        perror("Failed to allocate memory");
        exit(EXIT_FAILURE);
    }

    int upperBoundSqrt = (int) sqrt((double) *upperBound);
    for (int i = 2; i <= upperBoundSqrt; i++) {
        if (!composite[i]) {
            for (int j = i * i; j <= *upperBound; j += i) {
                composite[j] = true;
            }
        }
    }

    return composite;
}
