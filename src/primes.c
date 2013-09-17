// Program primes.c by Alan K Stewart
// Calculates prime numbers using the Sieve of Eratosthenes

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

int sieve(int);

int main(int argc, char** argv) {
    int num;

    if (argc == 1) {
        num = 100;
    } else if (argc > 2 || atoi(argv[1]) < 2) {
        printf("Usage: primes <number greater than 1>\n");
        exit(EXIT_FAILURE);
    } else {
        num = atoi(argv[1]);
    }

    printf("*** Prime numbers to %d ***\n", num);
    printf("\n\nThere are %d prime numbers\n", sieve(num));
    return 0;
}

int sieve(int num) {
    int N, k, m, mm, sqrtN, num_primes, line_count;
    char *n, *i, *j;

    N = (num - 1) / 2;
    num_primes = line_count = 1;
    n = (char*) calloc(N, sizeof(char));

    sqrtN = ((int) sqrt((double) 2 * N + 3)) + 1;
    for (k = 3, m = 0, i = n; k <= sqrtN; k += 2, ++m, ++i) {
        if (*i == 0) {
            for (mm = m + k, j = i + k; mm < N; mm += k, j += k) {
                *j = 1;
            }
        }
    }

    printf("\n2\t");
    for (k = 3, m = 0, i = n; m < N; k += 2, ++m, ++i) {
        if (*i == 0) {
            num_primes++;
            line_count++;
            if (line_count > 8) {
                line_count = 1;
                printf("\n");
            }
            printf("%d\t", k);
        }
    }

    free((char*) n);
    return num_primes;
}
