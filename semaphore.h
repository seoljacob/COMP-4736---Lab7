#include "spinlock.h"

/*----------xv6 sync lab----------*/
#define NSEM 10
extern int sem[NSEM];
extern struct spinlock li[NSEM];
int sem_init(int, int);
int sem_up(int);
int sem_down(int);
/*----------xv6 sync lab end----------*/
