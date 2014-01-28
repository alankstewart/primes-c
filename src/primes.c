// Program primes.c by Alan K Stewart
// Calculates prime numbers using the Sieve of Eratosthenes

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>

void eratosthenesSieve(int upperBound);

int main(int argc, char** argv) {
    int upperBound;

    if (argc == 1) {
        upperBound = 100;
    } else if (argc > 2 || atoi(argv[1]) < 2) {
        printf("Usage: primes <number greater than 1>\n");
        exit(EXIT_FAILURE);
    } else {
        upperBound = atoi(argv[1]);
    }

    eratosthenesSieve(upperBound);
    return EXIT_SUCCESS;
}

void eratosthenesSieve(int upperBound) {
    int i;
    _Bool *composite;

    if ((composite = malloc((upperBound + 1) * sizeof(_Bool))) == NULL) {
        perror("Failed to allocate memory");
        exit(EXIT_FAILURE);
    }

    int upperBoundSqrt = (int) sqrt((double) upperBound);
    for (i = 2; i <= upperBoundSqrt; i++) {
        if (!composite[i]) {
            for (int j = i * i; j <= upperBound; j += i) {
                composite[j] = true;
            }
        }
    }
    for (i = 2; i <= upperBound; i++) {
        if (!composite[i]) {
            printf("%d ", i);
        }
    }
    printf("\n");

    free(composite);
}
