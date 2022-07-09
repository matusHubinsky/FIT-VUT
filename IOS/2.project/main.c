/*
	 _._     _,-'""`-._
	(,-.`._,'(       |\`-/|
	    `-.-' \ )-`( , o o)
	          `-    \`_`"'-
*/

#include "main.h"
#include "init.h"
#include "water.h"

// SHARED MEMORY
int line_number;	// shared variable, serial line_number of process
int molecule;		// idk
FILE * file_ptr;	// file pointer
sem_t * sem_ptr;	// semaphore pointer
map * map_ptr;		// map pointer

int ox = 0;			// line_number of oxygens
int hy = 0;			// line_number of hydrogens
int qt = 0;			// maximum waiting time for queue
int mt = 0;			// maximu waiting time for molecule


// function for writing to file
void write_to_file(FILE *stream, char *format, ...) 
{
	sem_wait(map_ptr -> sem.out);
   	
   	// printing number of line is isolated
	map_ptr -> line_number++;
   	fprintf(file_ptr, "%d: ", map_ptr -> line_number);

   	// after printing number of line, starts default printing 
   	va_list args;
   	va_start(args, format);
   	vfprintf(stream, format, args);
   	va_end(args);
   	sem_post(map_ptr -> sem.out);
}


int main(int argc, char *argv[])
{
	// init and error handling 
	if (init(argc, argv) == -1)
	{
		clean_everything();
		exit(1);
	}
	
	// creating all oxygen process
	for (int ox_n = 1; ox_n < ox + 1; ox_n++)
	{
		pid_t ox_pid = fork();
		if (ox_pid == 0)
		{
			oxygen(ox_n, qt, mt);
		}

		if (ox_pid == -1) fprintf(stderr, "Error");
	}

	// creating all hydrogen process
	for (int hy_n = 1; hy_n < hy + 1; hy_n++)
	{
		pid_t hy_pid = fork();
		if (hy_pid == 0)
		{
			hydrogen(hy_n, qt);
		}

		if (hy_pid == -1) fprintf(stderr, "Error");
	}

    // parent needs to wait until the childs are dead
    while(wait(NULL) > 0);

    clean_everything();
    exit(0);
	return 0;
}