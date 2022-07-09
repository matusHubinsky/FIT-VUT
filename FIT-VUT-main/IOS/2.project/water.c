/*
	 _._     _,-'""`-._
	(,-.`._,'(       |\`-/|
	    `-.-' \ )-`( , o o)
	          `-    \`_`"'-
*/

#include "main.h"
#include "water.h"

// process OXYGEN
void oxygen(int id, int qt, int mt)
{
	write_to_file(file_ptr, "O %i: started\n", id);

	// waits fot a random time in interval from 0 to max queue waiting time
	usleep((rand() % (qt+1)) * 1000);

	write_to_file(file_ptr, "O %i: going to queue\n", id);

	// process will lock mutex semaphore and checks conditions
	sem_wait(map_ptr -> sem.mutex);
	// oxygen checks number of created molecules and number of atoms needed
	// if there is no more molecules left to create or no more atoms needed
	if (map_ptr -> rm_molecule == map_ptr -> molecule || map_ptr -> ox_count > map_ptr -> ox_max)
	{
		sem_post(map_ptr -> sem.mutex);
		write_to_file(file_ptr, "O %i: not enough H\n", id);
		exit(0);
	}
	// else process can continue to queue and molecule creation
	memory_lock(map_ptr -> ox++);
	memory_lock(map_ptr -> ox_count++);

	if (map_ptr -> hy >= 2)
	{
		// increase number of molecules
		memory_lock(map_ptr -> molecule++);
	
		// wakes up two hydrogens and decreases number of hydrogens in queue
		sem_post(map_ptr -> sem.hy);
		sem_post(map_ptr -> sem.hy);
		memory_lock(map_ptr -> hy -= 2);
	
		// wakes up one oxygen and decreases number of oxygens in queue 
		sem_post(map_ptr -> sem.ox);
		memory_lock(map_ptr -> ox -= 1);
	}
	else
	{
		// if these is not enough atoms to create molecule, process will unlock the mutex
		sem_post(map_ptr -> sem.mutex);
	}
	// and waits until more atoms come
	sem_wait(map_ptr -> sem.ox);
	write_to_file(file_ptr, "O %i: creating molecule %i\n", id, map_ptr -> molecule);
	// process locks the barrier before checking condition
	sem_wait(map_ptr -> sem.bar);	
	memory_lock(map_ptr -> count++);
	if (map_ptr -> count == 3)
	{
		sem_wait(map_ptr -> sem.turnslide2);
		sem_post(map_ptr -> sem.turnslide1);
	}
	// process unlocks the barrier after checking condition
	sem_post(map_ptr -> sem.bar);
	sem_wait(map_ptr -> sem.turnslide1);
	sem_post(map_ptr -> sem.turnslide1);

	// process waits for a random time in interval 0 to max molecule creation time
	usleep((rand() % (mt+1)) * 1000);
	write_to_file(file_ptr, "O %i: molecule %i created\n", id, map_ptr -> molecule);

	// process locks the barrier before checking condition
	sem_wait(map_ptr -> sem.bar);
	memory_lock(map_ptr -> count--);
	if (map_ptr -> count == 0)
	{
		sem_wait(map_ptr -> sem.turnslide1);
		sem_post(map_ptr -> sem.turnslide2);
	}
	// process unlocks the barrier after checking condition
	sem_post(map_ptr -> sem.bar);
	sem_wait(map_ptr -> sem.turnslide2);
	sem_post(map_ptr -> sem.turnslide2);

	// process unlocks the mutex
	sem_post(map_ptr -> sem.mutex);
	// the child must be killed
	exit(0);
}

// process HYDROGEN
void hydrogen(int id, int qt)
{
	write_to_file(file_ptr, "H %i: started\n", id);	
	
	// waits fot a random time in interval from 0 to max queue waiting time
	usleep((rand() % (qt+1)) * 1000);

	write_to_file(file_ptr, "H %i: going to queue\n", id);

	// process will lock mutex semaphore and checks conditions
	sem_wait(map_ptr -> sem.mutex);
	// oxygen checks number of created molecules and number of atoms needed
	// if there is no more molecules left to create or no more atoms needed
	if (map_ptr -> rm_molecule == map_ptr -> molecule || map_ptr -> hy_count > map_ptr -> hy_max)
	{
		sem_post(map_ptr -> sem.mutex);
		write_to_file(file_ptr, "H %i: not enough O or H\n", id);
		exit(0);
	}	
	// else process can continue to queue and molecule creation
	memory_lock(map_ptr -> hy++);
	memory_lock(map_ptr -> hy_count++);

	if (map_ptr -> hy >= 2 && map_ptr -> ox >= 1)
	{	
		// increase number of molecules
		memory_lock(map_ptr -> molecule++);
		
		// wakes up two hydrogens and decreases number of hydrogens in queue
		sem_post(map_ptr -> sem.hy);
		sem_post(map_ptr -> sem.hy);
		memory_lock(map_ptr -> hy -= 2);
		
		// wakes up one oxygen and decreases number of oxygens in queue 
		sem_post(map_ptr -> sem.ox);
		memory_lock(map_ptr -> ox -= 1);
	}
	else
	{
		// if these is not enough atoms to create molecule, process will unlock the mutex
		sem_post(map_ptr -> sem.mutex);
	}
	// and waits until more atoms come
	sem_wait(map_ptr -> sem.hy);
	write_to_file(file_ptr, "H %i: creating molecule %i\n", id, map_ptr -> molecule);
	// process locks the barrier before checking condition
	sem_wait(map_ptr -> sem.bar);
	memory_lock(map_ptr -> count++);
	
	if (map_ptr -> count == 3)
	{
		sem_wait(map_ptr -> sem.turnslide2);
		sem_post(map_ptr -> sem.turnslide1);
	}
	// process unlocks the barrier after checking condition
	sem_post(map_ptr -> sem.bar);
	sem_wait(map_ptr -> sem.turnslide1);
	sem_post(map_ptr -> sem.turnslide1);

	// process waits for a random time in interval 0 to max molecule creation time
	write_to_file(file_ptr, "H %i: molecule %i created\n", id, map_ptr -> molecule);

	// process locks the barrier before checking condition
	sem_wait(map_ptr -> sem.bar);
	memory_lock(map_ptr -> count--);

	if (map_ptr -> count == 0)
	{
		sem_wait(map_ptr -> sem.turnslide1);
		sem_post(map_ptr -> sem.turnslide2);
	}
	// process unlocks the barrier after checking condition
	sem_post(map_ptr -> sem.bar);
	sem_wait(map_ptr -> sem.turnslide2);
	sem_post(map_ptr -> sem.turnslide2);

	// the child must be killed
	exit(0);	
}