#ifndef RWMAIN_READERWRITER_H
#define RWMAIN_READERWRITER_H

#include <pthread.h>
#include <semaphore.h>

typedef struct { 
   sem_t lock; // binary semaphore (basic lock)
   sem_t writelock; // allow ONE writer/MANY readers 
   sem_t avoidStarve; // semaphore implemented to avoid stavation on writers.
   int readers; // #readers in critical section 
} rwlock_t; 

//rwlock_t rw;
void rwlock_init(rwlock_t *rw);
void rwlock_acquire_readlock(rwlock_t *rw);
void rwlock_release_readlock(rwlock_t *rw);
void rwlock_acquire_writelock(rwlock_t *rw);
void rwlock_release_writelock(rwlock_t *rw);
void* emulatReader(void *args);
void* emulatWriter(void *args);
void printar();

#endif //RWMAIN_READERWRITER_H