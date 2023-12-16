#include "types.h"
#include "stat.h"
#include "user.h"



int main()
{
  int ret1, ret2;
  int CHILDSEM=0;
  int PARENTSEM=1;
  
  sem_init(CHILDSEM, 0);
  sem_init(PARENTSEM, 0); 
  
  ret1 = fork();
  if(ret1 == 0) // current process is child 1
    {
      sem_down(CHILDSEM); // if negative, sleep till parent wakes up(sem_up) : negative
      printf(1, "I am child 1\n");
      sem_up(PARENTSEM); // signal parent that child 1 has finished
      exit();
    }
  else // parent
    {
      ret2 = fork();
      if(ret2 == 0) // current process is child 2
	{
	  sem_down(CHILDSEM); // sem [-2, 0] 
	  printf(1, "I am child 2\n");
	  sem_up(PARENTSEM);
	  exit();
	}
      else {

	sleep(2);

	//inspite of the sleep, parent should print first
	printf(1, "I am parent and I should print first\n");

	sem_up(CHILDSEM); // wake up child 1. 
	sem_down(PARENTSEM); // wait for child 1 to finish: negative
	
	printf(1, "Only one child has printed by now\n");

	sem_up(CHILDSEM); // wake up child 2
	sem_down(PARENTSEM); // wait for child 2 to finish: negative
	printf(1, "Both children have printed by now\n");
	
	wait();
	wait();
	
	exit();
      }
    }
}

