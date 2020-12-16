#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>
#include <ctype.h>
#include "readerwriter.h"
#define MAXCHAR 1000
#define MAXTHREADSPERCASE 12

   rwlock_t rw; // creating lock



int main(int argc, char *argv[] )
{
  
    rwlock_init(&rw); // init lock

    //printf("Start here we are\n" );
    FILE* ptr;
    char threatType[MAXCHAR];

    pthread_t threds[MAXTHREADSPERCASE]; // creating threads
   
    ptr= fopen("scenarios.txt","r");
    if(ptr == NULL)
        {
            printf("Error oppening file\n");
            return 1;
        }

        int scenarioCounter = 1;
    while (fgets(threatType, MAXCHAR, ptr) != NULL)
    {
        printf("\n\n\n\nScenario %d %s\n",scenarioCounter, threatType);
        scenarioCounter++;

    int i = 0;
    //chekin the thread type read or write.
     while(i< MAXTHREADSPERCASE)
        {
            //printf("\ndebuggin %d\n", i); 
         //printf("character %d = %c \n" ,i, threatType[i]);
         if(threatType[i] == 'r' || threatType[i] == 'R')
            {
                //printf("\nreading %i\n",i); 
                pthread_create(&threds[i], NULL, emulatReader, &rw);
            }
        else if(threatType[i] == 'w' || threatType[i] == 'W')
            {
               // printf("\nwriting %i\n",i);
                pthread_create(&threds[i], NULL, emulatWriter, NULL);
            }
        
        else
            {
                printf("not valid thread type. threat type could be r of w. please check scenarios.txt and make sure threads are valid, none space should be place within read or writes. ");
            }
         i++;
        }

    int j = 0;
    while( j<MAXTHREADSPERCASE)// joining threads 
        {
            pthread_join(threds[j], NULL);
            j++;
        }
    }
    //printar();
    fclose(ptr);
    printf("\nEnd of execution, to test different scenarios, modify the scenarios.txt file.\n" );

    return 0;
}
