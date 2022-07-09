   // bitset.h
   // Riešenie IJC-DU1, příklad a), 22.2.2022
   // Autor: MatúŠ Hubinský, xhubin04
   // Přeloženo: gcc 11.2.0

#ifndef bitset_H_
#define bitset_H_

#include <stdlib.h>
#include <assert.h>
#include <limits.h>

#include "error.h"

typedef unsigned long * bitset_t;

typedef unsigned long bitset_index_t;
 
#define UL_SIZE (CHAR_BIT * sizeof(unsigned long))

#define bitset_create(arr, arr_size) \
	unsigned long arr[arr_size /  UL_SIZE + 1]; \
	arr[0] = arr_size; \
	for (unsigned long i = 1; i < arr_size /  UL_SIZE + 1; i++) arr[i] = 0; \
	static_assert((unsigned long)arr_size > 0, "bitset_create: Chyba velkosti pola\n");

#define bitset_alloc(arr, arr_size) \
	bitset_t arr = calloc(arr_size /  UL_SIZE + 1, UL_SIZE); \
	arr[0] = arr_size; \
	if (arr == NULL) error_exit("bitset_alloc: Chyba alokace paměti"); 
	
#ifndef USE_INLINE

	#define bitset_free(arr) free(arr)

	#define bitset_size(arr) arr[0]

	#define bitset_setbit(arr, index, exp) \
		( (index > 0 || index < arr[0]) ? ((exp == 0 ? (arr[index / UL_SIZE + 1] &= ~(1UL << (index % UL_SIZE))) : (arr[index / UL_SIZE + 1] |= 1UL << (index % UL_SIZE)))) : (error_exit("Index %lu mimo rozsah 0..%lu", (unsigned long)index, (unsigned long)arr[0]), (int)1) )

	#define bitset_getbit(arr, index) \
		( (int)(index > 0 || index < arr[0]) ? (arr[index / UL_SIZE + 1] >> (index % UL_SIZE) & 1UL) : (error_exit("Index %lu mimo rozsah 0..%lu", (unsigned long)index, (unsigned long)arr[0]), (int)1) )

#else
	inline void bitset_free(bitset_t * arr)
	{
		if (arr == NULL)
		{
			error_exit("Wrong Pointer");
			fprintf(stderr, "Hello\n");s
			return;
		} 
		free(arr);	
	} 	

	inline unsigned long bitset_size(bitset_t arr)
	{
		return arr[0];
	} 
			
	inline void bitset_setbit(bitset_t arr, unsigned long index, unsigned long exp) 
	{
		if (index >= arr[0] || index < 0) error_exit("Index %lu mimo rozsah 0..%lu", (unsigned long)index, (unsigned long)arr[0]);
		if (exp != 0 && exp != 1) exp = 1;
		arr[index / sizeof(unsigned long) + 1] = (arr[index / sizeof(unsigned long) + 1] & ~(1UL << index % sizeof(unsigned long))) | (exp << (index % sizeof(unsigned long))); 
	}

	inline unsigned long bitset_getbit(bitset_t arr, unsigned long index) 
	{
		if (index >= arr[0] || index < 0) error_exit("Index %lu mimo rozsah 0..%lu", (unsigned long)index, (unsigned long)arr[0]);
		return (arr[index / sizeof(unsigned long) + 1] >> index % sizeof(unsigned long) & 1U);
	}

	#endif

#endif 