	# makefile
	#IJC-DU2, příklad a) 20.04.2022
	#Autor: MatúŠ Hubinský, xhubin04
	#Přeloežno: gcc 11.2.0

CC = gcc                              
CFLAGS = -std=c11 -pedantic -Wall -Wextra

.PHONY : all clear zip 

all: tail
	./tail -n 5 <soubor.txt
	./tail soubor.txt

tail.o: tail.c
	$(CC) $(CFLAGS) $< -c -o $@ 

clear:
	rm *.o *.gch tail xhubin04.zip

zip: 
	zip xhubin04.zip *.c *.h makefile