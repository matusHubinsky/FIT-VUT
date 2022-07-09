   // steg-decode.c
   // Riešenie IJC-DU1, příklad a), 22.2.2022
   // Autor: MatúŠ Hubinský, xhubin04
   // Přeloženo: gcc 11.2.0

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h> 
#include <string.h>

#include "ppm.h"
#include "error.h"
#include "bitset.h"
#include "eratosthenes.h"


int main(int argc, char * argv[])
{
	if (argc > 2) error_exit("Prilis veľa argumentov");
	struct ppm * arr = ppm_read(argv[1]);
	if (arr == NULL) error_exit ("Chyba pri vytvarani pola");

	FILE * file = fopen(argv[1], "rb");
	int size =  (3 * (arr -> xsize) * (arr -> ysize));

	bitset_alloc(primes, size + 1);
	eratosthenes(primes, size + 1);
		
	char * message = malloc((int)size / sizeof(unsigned long) * 2);
	char c = '\0';
	bool end = false;
	int bite_index = 0;
	int message_index = 0;;

	for (int i = 29; i < size; i++)
	{
		if (bitset_getbit(primes, i) == 1)
		{
			c |= (arr -> data[i] & (char)1 ) << bite_index;
            bite_index++;

            if (bite_index == 8)
            {
 				if (c == '\0')
				{
					message[message_index] = '\0';
					end = true;
					break;
				}
				else
				{
					message[message_index] = c;
            		message_index++;
	        		bite_index = 0;
	        		c = 0;
				}
            }
        }
    }
	
    if (message[message_index] != '\0') warning_msg("Zle zakončenie");
    
	if (end) fprintf(stderr, "%s\n", message);

	fclose(file);
	ppm_free(arr);
	bitset_free(primes);

	return 0;
}
