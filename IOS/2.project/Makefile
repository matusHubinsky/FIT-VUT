#
#	 _._     _,-'""`-._
#	(,-.`._,'(       |\`-/|
#	    `-.-' \ )-`( , o o)
#	          `-    \`_`"'-
#

.PHONY : all clear memory run test zip 

CC = gcc
CFLAGS = -std=gnu99 -Wall -Wextra -Werror -pedantic -pthread -lrt
BIN = proj2

all: $(BIN)

# .o files
init.o: init.c main.h
	$(CC) $(CFLAGS) $< -c -o $@

water.o: water.c main.h
	$(CC) $(CFLAGS) $< -c -o $@

main.o: main.c main.h init.h water.h
	$(CC) $(CFLAGS) $< -c -o $@

# bin
proj2: main.o init.o water.o
	$(CC) $(CFLAGS) $^ -o $@

# others
clear:
	rm *.o *.out *.txt proj2 proj2.zip

test:
	./proj2 1 1 10 10
	./proj2 1 2 10 10
	./proj2 2 1 10 10
	./proj2 2 2 10 10
	./proj2 3 5 10 10

zip: 
	zip proj2.zip *.c *.h Makefile

