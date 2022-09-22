   // primes.c
   // Riešenie IJC-DU1, příklad a), 22.2.2022
   // Autor: MatúŠ Hubinský, xhubin04
   // Přeloženo: gcc 11.2.0

#include "bitset.h"
#include "eratosthenes.h"

#define N 300000000LU

void print_primes(bitset_t arr, unsigned long target)
{	
	if (arr == NULL)
	{
		error_exit("Zly odkaz na pole");
		return;	
	}
    unsigned long primes[10];

    int k = 0;
    unsigned long i = target - 1;
    while (i > 0 && k < 10)
    {
        if (bitset_getbit(arr, i) == 1)
        {
            primes[k] = i; 
            k++;
        }
        i--;
    }
    for (int i = 9; i > -1; i--)
    {
        fprintf(stderr ,"%li \n", primes[i]);
    }
}

int main()
{
    clock_t start = clock();
    bitset_create(crr, N);
    eratosthenes(crr, N);
    print_primes(crr, N);
    fprintf(stderr, "Time = %.3g\n", (double)(clock()-start)/CLOCKS_PER_SEC);
    return 0;
}