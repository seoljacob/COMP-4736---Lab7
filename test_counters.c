#include "types.h"
#include "stat.h"
#include "user.h"

int main()
{
	int ret;
	int i;


	ucounter_init();
	// initialize the spinlock array
	uspinlock_init();

	ret = fork();

	//both parent and child increment the same counter 10000 times each
	for(i=0; i<10000; i++)
	{
		
		uspinlock_acquire(0); // acquire the lock
		ucounter_set(0, ucounter_get(0)+1);
		uspinlock_release(0); // release the lock
	}

	// current process is the child
	// parent will wait for the child to finish
	if(ret == 0)
	{
		exit();
	}
	// child process finished
	// parent prints the final value of the counter
	else
	{
		wait();
		printf(1, "%d\n", ucounter_get(0));
		//ideally this value should be 20000
		exit();
	}
}

