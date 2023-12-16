#include "types.h"
#include "stat.h"
#include "user.h"

#define CHILD_TURN_TO_PRINT 0
#define PARENT_TURN_TO_PRINT 1

// ucounter(0) -> 0: child's turn to print
// ucounter(0) -> 1: parent's turn to print
// parent sleeps on channel 1
// child sleeps on channel 2

int main()
{
    int ret;
    int i;

    uspinlock_init(); // initialize the spinlock array
    ucounter_init();  // initialize the ucounter array

    ret = fork();

    // initial ucounter value is 0 (child's turn to print)
    // child will print first

    if (ret == 0) // child process
    {
        for (i = 0; i < 10; i++)
        {
            uspinlock_acquire(0); // acquire the lock
            // if it is the parent's turn to print, sleep child on channel 2
            if (ucounter_get(0) == PARENT_TURN_TO_PRINT) // 1
            {
                ucv_sleep(2, 0); // sleep on channel 2
            }
            printf(1, "I am child\n");
            ucounter_set(0, ucounter_get(0) + 1); // increment to 1 (parent's turn to print)
            ucv_wakeup(1); // wake up the parent on channel 1
            uspinlock_release(0); // release the lock
        }
        exit(); // exit the child process
    }
    else
    {
        for (i = 0; i < 10; i++)
        {
            uspinlock_acquire(0); // acquire the lock
            // if it is the child's turn to print, sleep parent on channel 1
            if (ucounter_get(0) == CHILD_TURN_TO_PRINT) // 0
            {
                ucv_sleep(1, 0); // sleep on channel 1
            }
            printf(1, "I am parent\n");
            ucounter_set(0, ucounter_get(0) - 1); // decrement to 0 (child's turn to print)
            ucv_wakeup(2); // wake up the child on channel 2
            uspinlock_release(0); // release the lock
        }
        wait(); // wait for the child process to exit
        exit(); // exit the parent process
    }
}
