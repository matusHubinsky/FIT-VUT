/*
	 _._     _,-'""`-._
	(,-.`._,'(       |\`-/|
	    `-.-' \ )-`( , o o)
	          `-    \`_`"'-
*/

#include "init.h"

int init(int argc, char * argv[])
{
	if (argc != 5)
	{
		fprintf(stderr, "Invalid line_number of arguments\n");
		exit(1);
	} 

	char * ptr1; char * ptr2; char * ptr3; char * ptr4;
	ox = strtol(argv[1], &ptr1, 10);		// line_number of oxygens
	hy = strtol(argv[2], &ptr2, 10);		// line_number of hydrogens
	qt = strtol(argv[3], &ptr3, 10);		// maximum waiting time for queue
	mt = strtol(argv[4], &ptr4, 10);		// maximum waiting time for molecule

	if (!(ox > 0) || !(hy > 0))
	{
		fprintf(stderr, "Invalid arguments for line_number of oxygens or hydrogens\n");
		exit(1);
	}

	if (ptr1 != NULL && *ptr1 != 0)
	{
		fprintf(stderr, "Argument for oxygens must be a line_number\n");
		exit(1);	
	}

	if (ptr2 != NULL && *ptr2 != 0)
	{
		fprintf(stderr, "Argument for hydrogens must be a line_number\n");
		exit(1);	
	}

	if (qt < 0 || qt > 1000)
	{
		fprintf(stderr, "Invalid for waiting in queue\n");
		exit(1);		
	}

	if (mt < 0 || mt > 1000)
	{
		fprintf(stderr, "Invalid time for creating molecule\n");
		exit(1);		
	}

	if ((ptr3 != NULL && *ptr3 != 0) || (ptr4 != NULL && *ptr4 != 0))
	{
		fprintf(stderr, "Time arguments must be a line_number\n");
		exit(1);	
	}

	// creating proj2.out
    file_ptr = fopen("proj2.out", "w");
    
    // file error handling
    if (file_ptr == NULL)
    {
     	fprintf(stderr, "File can't be created\n");
    	return -1;
    }

    // file buffer
    setbuf(file_ptr, NULL);

    map_ptr = mmap(NULL, sizeof(struct map_t), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, 0, 0);

    // intializing semaphores
	sem_t * hy_ptr = sem_open("/xhubin04.ios.hy", O_CREAT, -1, 0);
	sem_t * ox_ptr = sem_open("/xhubin04.ios.ox", O_CREAT, -1, 0);
	sem_t * sem_ptr = sem_open("/xhubin04.ios.sem", O_CREAT, -1, 1);
	sem_t * out_ptr = sem_open("/xhubin04.ios.out", O_CREAT, -1, 1);
	sem_t * bar_ptr = sem_open("/xhubin04.ios.bar", O_CREAT, -1, 3);
	sem_t * turn1_ptr = sem_open("/xhubin04.ios.turnslide1", O_CREAT, -1, 0);
	sem_t * turn2_ptr = sem_open("/xhubin04.ios.turnslide2", O_CREAT, -1, 1);

	if (sem_ptr == SEM_FAILED || hy_ptr == SEM_FAILED || ox_ptr == SEM_FAILED || bar_ptr == SEM_FAILED || 
		turn1_ptr == SEM_FAILED || turn2_ptr == SEM_FAILED || bar_ptr == SEM_FAILED)
	{
		fprintf(stderr, "Semaphore can't be initialized\n");
		return -1;
	} 

	int min = (hy/2 <= ox) ? hy/2 : ox;

	// initializing shred
	map_ptr -> ox = 0;
	map_ptr -> hy = 0;
	map_ptr -> ox_max = min; 
	map_ptr -> hy_max = min * 2;
	map_ptr -> ox_count = 1;
	map_ptr -> hy_count = 1;
	map_ptr -> rm_molecule = min;
	map_ptr -> count = 0;
	map_ptr -> line_number = 0;
	map_ptr -> molecule = 0;
	map_ptr -> creating = false;
	map_ptr -> sem.ox = hy_ptr;
	map_ptr -> sem.hy = ox_ptr;
	map_ptr -> sem.bar = bar_ptr;
	map_ptr -> sem.out = out_ptr;
	map_ptr -> sem.turnslide1 = turn1_ptr;
	map_ptr -> sem.turnslide2 = turn2_ptr;
	map_ptr -> sem.mutex = sem_ptr;

	return 0; 
}

void clean_everything()
{
	// cleaning all semaphores
	if (map_ptr -> sem.ox != NULL)
	{
		sem_close(map_ptr -> sem.ox);
		sem_unlink("/xhubin04.ios.ox");
	}
	if (map_ptr -> sem.hy != NULL)
	{
		sem_close(map_ptr -> sem.hy);
		sem_unlink("/xhubin04.ios.hy");
	}
	if (map_ptr -> sem.mutex != NULL)
	{
		sem_close(map_ptr -> sem.mutex);
		sem_unlink("/xhubin04.ios.sem");
	}
	if (map_ptr -> sem.bar != NULL)
	{
		sem_close(map_ptr -> sem.bar);
		sem_unlink("/xhubin04.ios.bar");
	}
	if (map_ptr -> sem.out != NULL)
	{
		sem_close(map_ptr -> sem.out);
		sem_unlink("/xhubin04.ios.out");
	}
	if (map_ptr -> sem.turnslide1 != NULL)
	{
		sem_close(map_ptr -> sem.turnslide1);
		sem_unlink("/xhubin04.ios.turnslide1");
	}
	if (map_ptr -> sem.turnslide2 != NULL)
	{
		sem_close(map_ptr -> sem.turnslide2);
		sem_unlink("/xhubin04.ios.turnslide2");
	}
	if (file_ptr != NULL)
	{
		fclose(file_ptr);
	}
	if (munmap(map_ptr, sizeof(struct map_t)) == -1)
	{
		fprintf(stderr, "Error while unmaping map\n");
		exit(1);	
	}
}
