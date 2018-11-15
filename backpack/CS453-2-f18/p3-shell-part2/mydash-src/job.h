#ifndef JOBS_H
#define JOBS_H

#include "../../list/include/List.h"
#include <sys/types.h>
#include <unistd.h>


#define ON 1
#define DONE 0
#define PROB 1
#define NORM 0
#define MAXPID 20

typedef struct jobs * jobPtr;
typedef struct jobs Jobs;

struct jobs {
    int pid;
	int job_num;	
	char* cmd;
	int status;
	int state;
};

char* isAmpersand(char*);

char* handle_ampersand(char*);

jobPtr job_maker(const int, const char*, const int); 

int equals (const void *,const void *);

char* toString (const void*);

void freeObject (void*);

int execCmd(char *, char **);

int start_background_job(char*, char**, int);

int start_job(char*, char**);


void log_background_job(int, char*);

//void update_completed_jobs();

//void remove_completed_jobs();

int process_state(int);

int exit_status(int);

#endif