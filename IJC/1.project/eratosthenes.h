   // eratostenes.h
   // Riešenie IJC-DU1, příklad a), 22.2.2022
   // Autor: MatúŠ Hubinský, xhubin04
   // Přeloženo: gcc 11.2.0

#ifndef ERATOSTHENES_H_
#define ERATOSTHENES_H_

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#include "bitset.h"

void eratosthenes(bitset_t arr, unsigned long target);

#endif