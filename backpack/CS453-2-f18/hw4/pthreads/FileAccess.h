//FileAccess.h
//Author: Tucker Ferguson
//October 19

#include <stdlib.h>
#include <pthread.h>
#include <stdio.h>

#ifndef _FILEACCESS_H
#define _FILEACCESS_H

typedef struct fileaccess FileAccess;
typedef struct fileaccess * fileaccess_init;

struct fileaccess{
   long int sum;
   long int max;
   long int now;
    pthread_mutex_t mutex;
    pthread_cond_t waitForAccess;
    pthread_cond_t done;
   void (*setAlarm) (fileaccess_init, long int);
   void (*tick) (fileaccess_init);
   void (*startAccess) (fileaccess_init,long int);
   void (*endAccess) (fileaccess_init, long int);
};

fileaccess_init monitorBuilder(int);
void startAccess(fileaccess_init,long int);
void endAccess(fileaccess_init, long int);

#endif /* _FILEACCESS_H */