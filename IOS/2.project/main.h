/*
	 _._     _,-'""`-._
	(,-.`._,'(       |\`-/|
	    `-.-' \ )-`( , o o)
	          `-    \`_`"'-
*/

#ifndef _MAIN_H
#define _MAIN_H

#include <stdbool.h>
#include <fcntl.h> 
#include <math.h>

#include <semaphore.h>

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <stdarg.h>

#include <sys/mman.h>          
#include <sys/stat.h>
#include <sys/wait.h>


#define memory_lock(statement) \
sem_wait(map_ptr -> sem.out); \
statement; \
sem_post(map_ptr -> sem.out);


typedef struct sem_struct
{
	sem_t * ox;
	sem_t * hy;
	sem_t * bar;
	sem_t * out;
	sem_t * turnslide1;
	sem_t * turnslide2;
	sem_t * mutex;
} sem;

typedef struct map_t
{
	int ox;
	int hy;
	int ox_max;
	int hy_max;
	int ox_count;
	int hy_count;
	int rm_molecule;
	int count;
	int line_number;
	int molecule;
	bool creating; 
	struct sem_struct sem;
} map;

extern int line_number;			// shared variable, serial line_number of process
extern int molecule;			// idk
extern FILE * file_ptr;			// file pointer
extern sem_t * sem_ptr;			// semaphore pointer
extern map * map_ptr;	// map pointer

extern int ox;			// line_number of oxygens
extern int hy;			// line_number of hydrogens
extern int qt;			// maximum waiting time for queue
extern int mt;			// maximu waiting time for molecule


void write_to_file(FILE *stream, char *format, ...);

#endif