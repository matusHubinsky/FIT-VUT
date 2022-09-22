   // bitset.c
   // Riešenie IJC-DU1, příklad a), 22.2.2022
   // Autor: MatúŠ Hubinský, xhubin04
   // Přeloženo: gcc 11.2.0

#include "bitset.h"

#ifdef USE_INLINE

	extern void bitset_free(bitset_t arr);	
	extern unsigned long bitset_size(bitset_t arr);
	extern void bitset_setbit(bitset_t arr, unsigned long index, unsigned long exp);
	extern unsigned long bitset_getbit(bitset_t arr, unsigned long index);
	
#endif		