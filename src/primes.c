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
    return 0;
}

void eratosthenesSieve(int upperBound) {
    int upperBoundSqrt = (int) sqrt((double) upperBound);

    _Bool *isComposite = malloc((upperBound + 1) * sizeof(_Bool));
    for (int m = 2; m <= upperBoundSqrt; m++) {
        if (!isComposite[m]) {
            printf("%d ", m);
            for (int k = m * m; k <= upperBound; k += m) {
                isComposite[k] = true;
            }
        }
    }
    for (int m = upperBoundSqrt; m <= upperBound; m++) {
        if (!isComposite[m]) {
            printf("%d ", m);
        }
    }
    printf("\n");

    free(isComposite);
}
