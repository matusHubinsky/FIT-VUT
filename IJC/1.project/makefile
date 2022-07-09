   # makefile
   # Riešenie IJC-DU1, příklad a), 22.2.2022
   # Autor: MatúŠ Hubinský, xhubin04
   # Přeloženo: gcc 11.2.0

CC = gcc                              
CFLAGS = -O2 -g -std=c11 -pedantic -Wall -Wextra

.PHONY : all run val clear zip 

all: primes primes-i steg-decode 
	./primes | factor
	./primes-i | factor
	./steg-decode du1-obrazek.ppm

bitset.o: bitset.c bitset.h
	$(CC) $(CFLAGS) $< -c -o $@ 

eratosthenes.o: eratosthenes.c eratosthenes.h
	$(CC) $(CFLAGS) $< -c -o $@

error.o: error.c error.h
	$(CC) $(CFLAGS) $< -c -o $@

primes.o: primes.c
	$(CC) $(CFLAGS) $< -c -o $@

ppm.o: ppm.c ppm.h error.h
	$(CC) $(CFLAGS) $< -c -o $@

steg-decode.o: steg-decode.c
	$(CC) $(CFLAGS) $< -c -o $@	

primes:	primes.o eratosthenes.o error.o bitset.o
	$(CC) $(CFLAGS) $^ -o $@ -lm

primes-i: primes.o eratosthenes.o error.o bitset.o
	$(CC) $(CFLAGS) -DUSE_INLINE $^ -o $@ -lm

steg-decode: bitset.o error.o eratosthenes.o ppm.o steg-decode.o
	$(CC) $(CFLAGS) $^ -o $@	

val:
	valgrind ./primes --leakcheck=full

clear:
	rm *.o *.gch primes-i primes xhubin04.zip

zip: 
	zip xhubin04.zip *.c *.h makefile
