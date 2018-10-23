
//FileAccess.c
//Author: Tucker Ferguson
//October 19
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>
#include <time.h>
#include <FileAccess.h>
static void setAlarm(fileaccess_init, long int);
static void tick(fileaccess_init);

fileaccess_init monitorBuilder(int maxProcess){
    fileaccess_init monitor;
    monitor = (fileaccess_init)malloc(sizeof(FileAccess));
    (*monitor).max = maxProcess;
    (*monitor).sum = 0;
    monitor->setAlarm = setAlarm;
    monitor->tick = tick;
    pthread_cond_init(&(monitor->waitForAccess),NULL);
    pthread_mutex_init(&(monitor->mutex),NULL);
    return monitor;
}

void startAccess(fileaccess_init monitor, long int pid){
    if(!(pid > monitor->max)){
        //fprintf(stderr,"pid: %ld\n", pid);
        pthread_mutex_lock(&(monitor->mutex));
        //int checker = monitor->sum + pid;
        fprintf(stderr,"thread %ld starting up\n",pid);
        while(monitor ->sum+pid > monitor->max){
            pthread_cond_wait(&(monitor->waitForAccess), &(monitor->mutex));
        }
            fprintf(stderr, "Thread %ld starting file access\n",pid);
            monitor->sum += pid;
            pthread_mutex_unlock(&(monitor->mutex));
            sleep(1);
    }
    
}
void endAccess(fileaccess_init monitor, long int pid){
    pthread_mutex_lock(&(monitor->mutex));
    monitor->sum -= pid;
    pthread_cond_broadcast(&((*monitor).waitForAccess));
     fprintf(stderr, "Thread %ld ending file access\n",pid);
    pthread_mutex_unlock(&(monitor->mutex));
}

void setAlarm(fileaccess_init monitor, long int period)
{
	pthread_mutex_lock(&(monitor->mutex));

	while (monitor->now < period) {
        pthread_cond_wait(&(monitor->done),&(monitor->mutex));
        monitor->now++;

	}
	pthread_mutex_unlock(&(monitor->mutex));
}

void tick(fileaccess_init monitor)
{
	pthread_mutex_lock(&(monitor->mutex));
	monitor->now++;
	pthread_cond_broadcast(&(monitor->waitForAccess));
	pthread_mutex_unlock(&(monitor->mutex));
}