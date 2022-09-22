   // ppm.c
   // Riešenie IJC-DU1, příklad a), 22.2.2022
   // Autor: MatúŠ Hubinský, xhubin04
   // Přeloženo: gcc 11.2.0

#include "ppm.h"
#include "error.h"

struct ppm * ppm_read(const char * filename)
{	
	FILE * file = fopen(filename, "rb");
	struct ppm * arr;

	if (file == NULL)
	{
		warning_msg("Nepodarilo sa načítať obrázok");
		return NULL;
	}

    char binary_type[2] = {0};
	unsigned xsize, ysize, color;
	
	if (!fscanf(file, "%s %u %u %u ", binary_type, &xsize, &ysize, &color)) error_exit("Chyba pri nacitani paramterov obrazka");
	
	if (strcmp(binary_type, "P6")) error_exit("Zly format");	
	if (xsize <= 0 && ysize <= 0) error_exit("Zla velkost obrazka");
	if (color != 255) error_exit("Zla hodnota farby");
	
	int buffer = 3 * xsize * ysize;
	if (buffer > BUFFER_LIMIT) error_exit("Buffer je moc velky");

	arr = malloc(sizeof(struct ppm) + buffer);
	arr -> xsize = xsize;
	arr -> ysize = ysize;

	if (!fread(arr -> data, 1, buffer, file)) error_exit("Chyba pri citani suboru");
	if (ferror(file)) error_exit("Chyba pri citani suboru");
	if (arr -> data == NULL) warning_msg("Chyba alokace");

	fclose(file);	
	return arr;
}

void ppm_free(struct ppm *p)
{
	p -> xsize = 0;
	p -> ysize = 0;
	free(p);
}
