#include <string.h>
#include <stdio.h>
#include <time.h>
#include <ring.h>
#include <signal.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>
pthread_mutex_t mutex;
int dFlag = 0;

static struct {
    int curr;
    char log[MAX_LOG_ENTRY][MAX_STRING_LENGTH];
} buff;
static void dump_buffer();

 void * threadStart(void* data){
    while(1){
        sleep(alarm_interval);
        dump_buffer();
    }
}
void init_buffer()
{
   // dFlag = 1; // knows to dump
    printf("RING BUFFER: Initialize the ring buffer\n");
    printf("RING BUFFER: Successfully started the backup thread %ld\n", (long) pthread_self());
    int i;
    for(i = 0; i < MAX_LOG_ENTRY; i++) {
        buff.log[i][0]='\0';
    }
    buff.curr = 0;
    pthread_t backUp;
    pthread_mutex_init(&mutex, NULL);
    pthread_create(&backUp, NULL, threadStart, NULL);          
}
/**
 * Return the current timestamp (localtime) from the system.
 */
static char *getTimeString()
{
    time_t myTime = time(NULL); //this is a system call
    char *timeString = ctime(&myTime);
    timeString[strlen(timeString)-1] = '\0'; //erase the newline at the end
    return timeString;
}

void log_msg(char *entry)
{
    if (entry == NULL) {
        printf("Skipping null log entry!\n");
        return;
    }
    printf("Adding log entry into buffer\n");
    char *timeString = getTimeString();
    int idx = buff.curr % MAX_LOG_ENTRY;
    snprintf(buff.log[idx], MAX_STRING_LENGTH, "%s -- %s", timeString, entry);
    buff.curr++;
    dump_buffer();
}
/*
 * Right now this is just printing to the console. We want to change this to
 * write to a file (log_name) and we want to use signals to trigger the logging
 * event. This also needs to be fixed so that it prints the log messages in the
 * right order (from the oldest to the newest).
 *
 * This method should write all the current entries to disk in the right order
 * (from the oldest to the newest). We will use the constant log_name as the
 * name of the file.
 */
static void dump_buffer()
{   
    FILE *f = fopen(log_name, "w");
    int i;
    for(i = 0; i < MAX_LOG_ENTRY; i++) {
        pthread_mutex_lock (&mutex);
        char *timeString = getTimeString();
        //int idx = buff.curr % MAX_LOG_ENTRY;
        fprintf(f, "log %d:%s--[%ld]: \n", i,timeString,(long) pthread_self());
        pthread_mutex_unlock(&mutex);
    }
    fclose(f);
    
}
