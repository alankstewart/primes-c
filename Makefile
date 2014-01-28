default: all

all: primes

clean:
	rm -f primes

primes: src/primes.c
	gcc -O3 -lm  src/primes.c -o primes

debug:
	gcc -O3 -lm -DDEBUG src/primes.c -o primes

bench: primes
	./primes 100

