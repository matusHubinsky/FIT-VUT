/*   
	tail.c
	IJC-DU2, příklad a) 20.04.2022
	Autor: MatúŠ Hubinský, xhubin04
	Přeloežno: gcc 11.2.0
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>

#define MAX_LENGTH 4095


int main(int argc, char *argv[])
{
	FILE * file;
	int lines;

	// error edge case handling
	if (argc < 1)
	{
		// maybe this is not a mistake and I should print
		// 10 last lines from STDIN
		fprintf(stderr, "Error: No arguments\n");
		return errno;
	}

	// if there are two arguments, lines will be read from a file
	if (argc == 2)
	{
		file = fopen(argv[1], "r");
		if (file == NULL)
		{
			fprintf(stderr, "An error occured when trying to open a file %d\n", errno);
			exit(-1);
		}
		lines = 0;
	}
	else
	{
		file = stdin;
		lines = 10;
		if (argc == 3)
		{
			if (strcmp(argv[1], "-n") == 0)
			{
				char * ptr;
				lines = strtol(argv[2], &ptr, 10);				
			
				if (ptr != NULL && *ptr != 0)	
				{
					fprintf(stderr, "Invalid number of lines\n");
					exit(-1);
				}
				// lines can't be less than one
				if (lines < 1)
				{
					fprintf(stderr, "Error: Can't print less than one line\n");
					exit(-1);
				}
			} 	
			else
			{
				fprintf(stderr, "Invalid line arguments\n");
				exit(-1);
			}
		}
		else if (argc != 1)
		{
			fprintf(stderr, "Too many arguments %d\n", argc);
			exit(-1);	
		}
	}
	int size = lines;
	if (lines == 0) size = 1000;

	// preparing string array
	char ** char_array = malloc(size * sizeof(char *));
	if (char_array == NULL)
	{
		fprintf(stderr, "Value of errno: %d\n", errno);
		exit(-1);
	}
	
	// alocating memory for lines
	for (int i = 0; i < size; i++)
	{
		char_array[i] = malloc(MAX_LENGTH * sizeof(char));	
	}

	int lines_file = 0;   
	int characters = 0;
	
	// loading lines into array
	for (char c = fgetc(file); c != EOF; c = fgetc(file))
	{
		if (c == '\n')
		{
			if (lines == 0) char_array[lines_file][characters] = '\0';
			else char_array[lines_file % lines][characters] = '\0';
			lines_file++;
			characters = 0;	
		} 
		else if (characters < MAX_LENGTH)
		{
			if (lines == 0) char_array[lines_file][characters] = c;
			else char_array[lines_file % lines][characters] = c;
			characters++;	
		}
	}
	if (size > lines_file) size = lines_file;

	// printing lines
	for (int i = 0; i < size; i++)
	{
		printf("%s\n", char_array[i]);
	}

	return 0;
}