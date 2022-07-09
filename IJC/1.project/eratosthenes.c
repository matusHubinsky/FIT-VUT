   // eratosthenes.c
   // Riešenie IJC-DU1, příklad a), 22.2.2022
   // Autor: MatúŠ Hubinský, xhubin04   
   // Přeloženo: gcc 11.2.0

#include "eratosthenes.h" 


void eratosthenes(bitset_t arr, unsigned long target)
{
    if (arr == NULL) warning_msg("Zly odkaz na pole");
    if (target < 2) warning_msg("Neexistuju ziadne prvocisla mensie ako 2");

    bitset_setbit(arr, 1, 0);
    bitset_setbit(arr, 2, 1);
    
    if (target > 3)
    {
        for (unsigned long i = 3; i < target; i += 2)
        {   
            if (i%2 == 1) bitset_setbit(arr, i, 1); 
        }
        for (unsigned long i = 3; i*i < target; i += 2)
        {
            if (bitset_getbit(arr, i) == 1)
            {
                for (unsigned long j = i*i; j < target; j += 2*i)
                {
                    bitset_setbit(arr, j, 0);
                }
            }
        }    
    }
}
