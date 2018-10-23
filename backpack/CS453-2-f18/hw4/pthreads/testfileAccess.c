//FileAccess.c
//Author: Tucker Ferguson
//October 19

#include <FileAccess.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <signal.h>
#include <time.h>

void* fileOperation(void * arg);
void signalHandler(int);

int numThreads;
int count;
int interations;
int period = 30;
fileaccess_init fileAccess;
void signalHandler(int);

pthread_mutex_t mutex;
pthread_t *threads;

int main(int argc, char** argv)
{
    if (argc < 4)
    {
        fprintf(stderr, "usage: ./driver <numberThreads> <max sum> <interations>\n");
        exit(EXIT_FAILURE);
    }
    numThreads = atoi(argv[1]);
    count = atoi(argv[2]);
    interations = atoi(argv[3]);
    
    if (numThreads > 32){
        fprintf(stderr,"Usage %s Too many threads specified. Defaulting to 32.\n", argv[0]);
        numThreads = 32;
    }
    fileAccess = monitorBuilder(numThreads);
	signal(SIGALRM, signalHandler);
	alarm(1);
   pthread_mutex_init(&mutex, NULL);
   threads = (pthread_t *) malloc(sizeof(pthread_t)*numThreads);
    int i;
    for (i = 0; i < numThreads; ++i)
    {   
        long int pid = rand() % count;
        pthread_create(&(threads[i]), NULL, fileOperation, (void*)pid);
    }
    for (i = 0; i < numThreads; ++i)
    {
        pthread_join(threads[i], NULL);
    }
     pthread_mutex_destroy(&mutex);
    exit(0);
}


static int get_my_index(void)
{
    int i;
    pthread_mutex_lock(&mutex);
    for (i=0; i<numThreads; i++)
    {
        if (threads[i] == pthread_self())
        {
            pthread_mutex_unlock(&mutex);
            return i;
        }
    }
    pthread_mutex_unlock(&mutex);
    return -1; /* we have a problem if we reach this statement */
}

void* fileOperation(void* arg)
{  
    int i;
    int id = get_my_index();
    for(i=0; i < interations; i++){
    //(*fileAccess->setAlarm)(fileAccess,period);
    startAccess(fileAccess,(int)id);
    //sleep(1);
    endAccess(fileAccess,(int)id);
    return NULL;
    }
    pthread_exit(NULL);
    
}
void signalHandler(int signo)
{
	fileAccess->tick(fileAccess);
	alarm(1); //reset alarm
}
