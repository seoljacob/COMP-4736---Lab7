/*----------xv6 sync lab----------*/
#include "types.h"
#include "x86.h"
#include "uspinlock.h"
#include "spinlock.h"

//TODO: define an array of NLOCK uspinlocks
typedef struct {
    uint locked; // lock status
} uspinlock_t;

// array of NLOCK spinlocks
uspinlock_t spinlocks[NLOCK]; 

int
uspinlock_init(void)
{
  for (int i = 0; i < NLOCK; i++) {
    spinlocks[i].locked = 0; // set lock status to unlocked
  }
  return 0;
}

int
uspinlock_acquire(int index)
{

  // xchg() atomically swaps a and b, returning the original value of a

  // if the lock is held(original value 1), spin until it is released
  // if the lock is free(original value 0), acquire the lock (set to 1)
  while (xchg(&spinlocks[index].locked, 1) != 0) {
      // spin until lock is acquired
  }
  return 0;
}

int
uspinlock_release(int index)
{
  spinlocks[index].locked = 0; // set lock status to unlocked
  return 0;
}

int
uspinlock_holding(int index)
{
  // return 0 if free, 1 if held
  return spinlocks[index].locked; // return lock status

}
/*----------xv6 sync lock end----------*/
