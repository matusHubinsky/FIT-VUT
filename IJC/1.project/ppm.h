   // ppm.h
   // Riešenie IJC-DU1, příklad a), 22.2.2022
   // Autor: MatúŠ Hubinský, xhubin04
   // Přeloženo: gcc 11.2.0

#ifndef PPM_H_
#define PPM_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_LIMIT 8000*8000*3

struct ppm {
    unsigned xsize;
    unsigned ysize;
    char data[];
 };

struct ppm * ppm_read(const char * filename);

void ppm_free(struct ppm *p);


#endif