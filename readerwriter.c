#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>
#include <ctype.h>
#define MAXCHAR 1000


typedef struct { 
   sem_t lock; // binary semaphore (basic lock)
   sem_t writelock; // allow ONE writer/MANY readers
   sem_t avoidStarve; // semaphore implemented to avoid stavation on writers.
   int readers; // #readers in critical section 
} rwlock_t; 

//rwlock_t rw; // creating lock

void rwlock_init(rwlock_t *rw) { 
   rw->readers = 0; 
   sem_init(&rw->lock, 0, 1); 
   sem_init(&rw->writelock, 0, 1); 
   sem_init(&rw->avoidStarve, 0, 1);
   printf("Semaphores status: Initialized\n\n");
} 
void rwlock_acquire_readlock(rwlock_t *rw) { 
   sem_wait(&rw->avoidStarve);
   sem_post(&rw->avoidStarve); 
   sem_wait(&rw->lock);
   rw->readers++; 
   printf("read lock active, critical section block for writers\n");
   if (rw->readers == 1) // first reader gets writelock 
       sem_wait(&rw->writelock);
   sem_post(&rw->lock);
} 
void rwlock_release_readlock(rwlock_t *rw) { 
   sem_wait(&rw-> lock); 
   rw->readers--; 
   if (rw->readers == 0){ // last reader lets it go 
      sem_post(&rw->writelock);      
      printf("critical section clear from readers\n");} 
   sem_post(&rw->lock);
   printf("reader left the critical section, remaining readers in critical section =%d \n", rw->readers);
   //printf("release a reader --->number of readers in critical section = %d" ,rw->readers );
} 
void rwlock_acquire_writelock(rwlock_t *rw) { 
   sem_wait(&rw->avoidStarve);
   sem_wait(&rw->writelock);
    printf("writer is in the critical section\n");
} 
void rwlock_release_writelock(rwlock_t *rw) { 
   sem_post(&rw->avoidStarve);
   sem_post(&rw->writelock); 

} 

rwlock_t rw; // creating lock

void printar()
{
    printf("printtest");
} 
void* emulatReader(void *args) {
    rwlock_acquire_readlock(&rw);

    int x = 0, T;
    int i, j;
        T = rand() % 10000;
        for(i = 0; i < T; i++)
        {
            for(j = 0; j < T; j++)
                    {x = i * j;}
        }

    rwlock_release_readlock(&rw);
    printf("(r) Read thread procces completed\n");
    //printf("Read performed --->number of readers in critical section = %s" ,rw->readers );
    return NULL;
}

void* emulatWriter(void *args) {
   
    rwlock_acquire_writelock(&rw);

    int x = 0, T;
    int i, j;
        T = rand() % 10000;
        for(i = 0; i < T; i++)
        {
            for(j = 0; j < T; j++)
                    {x = i * j;}
        }

    rwlock_release_writelock(&rw);
    printf("(w) Write thread proccess completed\n");
    return NULL;
}

