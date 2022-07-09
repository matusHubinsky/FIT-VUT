   // error.c
   // Riešenie IJC-DU1, příklad a), 22.2.2022
   // Autor: MatúŠ Hubinský, xhubin04
   // Přeloženo: gcc 11.2.0

#include "error.h"

void warning_msg(const char *fmt, ...)
{
	va_list args;
	va_start(args, fmt);
	fprintf(stderr, "Chyba: ");
	vfprintf(stderr, fmt, args);
	fprintf(stderr, "\n");
	va_end(args);	
}

void error_exit(const char *fmt, ...)
{
	warning_msg(fmt);
	exit(1);
}