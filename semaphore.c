/*----------xv6 sync lab----------*/
#include "types.h"
#include "x86.h"
#include "defs.h"
#include "semaphore.h"

char* dum = "JJ-Jacob"; // dummy name for lock
int sem[NSEM]; // array of semaphores
struct spinlock li[NSEM]; // array of spinlocks

// initialize semaphore at index to value val
int
sem_init(int index, int val)
{
	initlock(&li[index],dum); // initialize lock to protect semaphore
	acquire(&li[index]); // acquire lock to ensure mutual exclusion
	sem[index]=val; // set semaphore value
	release(&li[index]); // release lock
  return 0;
}

// up operation on semaphore at index
// wake up one process waiting on semaphore
int
sem_up(int index) 
{
	acquire(&li[index]); 
	sem[index]=sem[index]+1; 
	newwakeup((void *) (&sem[index])); // wake up one process
	release(&li[index]);
  return 0;
}

// down operation on semaphore at index
int
sem_down(int index)
{
	acquire(&li[index]);
	sem[index]=sem[index]-1;
	if(sem[index]<0){ // means no more resources available
		sleep((void *) (&sem[index]),&li[index]); // puts process to sleep
	}
	release(&li[index]);
  return 0;
}

/*----------xv6 sync lab end----------*/
