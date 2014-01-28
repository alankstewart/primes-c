default: all

all: primes

clean:
	rm -f primes primes.out

primes: src/primes.c
	gcc -O3 src/primes.c -lm -o primes

bench: primes
	./primes 100

