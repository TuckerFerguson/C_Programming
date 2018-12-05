#include "job.h"
#include <string.h>
#include <stdio.h>
#include "mydash.h"
#include <signal.h>
#include <pwd.h>
#include "../../list/include/List.h"

//struct job* jobPtr;
char *temp;
int jobID;
void init_job_manager(void);
void print_jobs(void);
void init_job_manager(void);
void update_completed_jobs(void);
void remove_completed_jobs(void);
void job_creation_printout(jobPtr job);
void free_jobs(void);
ListPtr jobs;
ListPtr jobsList;
struct list* activeJobs;
char* isAmpersand(char* cmd)
{	
	printf("cmd for ampersand %s\n",cmd);
	char* copy = malloc(strlen(cmd) + 1);
	strncpy(copy,cmd,strlen(cmd) + 1);
	copy = strchr(copy,'&');
	return copy;
}

jobPtr job_maker(const int pid,const char* cmd, int job_num)
{
	jobPtr newJob = (jobPtr) malloc (sizeof(Jobs));
	newJob->pid = pid;
	newJob->job_num = job_num;
	newJob->cmd = (char *)malloc(sizeof(char)*(strlen(cmd)+1));
	newJob->state = ON;
	newJob->status = NORM;
	strcpy(newJob->cmd,cmd);
	return newJob;
}

void init_job_manager()
{
    jobs = createList(equals, toString, freeObject);
    jobID = 0;
}


 int start_background_job(char* line, char** tokenized_command_and_args, int index_of_ampersand)
 {
     remove_ampersand(tokenized_command_and_args, index_of_ampersand);
     return execCmd(line, tokenized_command_and_args);
 }

 void log_background_job(int pid, char* line)
 {
     char* copy = (char*)malloc(strlen(line) + 1 *sizeof(char));
     strcpy(copy, line);
     Jobs* job = job_maker(pid, copy, ++jobID);
     NodePtr node = createNode(job);
     addAtRear(jobs, node);
     job_creation_printout(job);
 }

int start_job(char* line, char** tokenized_command_and_args)
 {
    return execCmd(line, tokenized_command_and_args);
 }

 int execCmd(char* line, char** tokenized_command_and_args)
{   
    printf("command: %s\n ",line);
    execvp(line, tokenized_command_and_args);
    err_ret("Couldn't execute: %s", line);
     return FALSE;
 }

void print_jobs()
 {
     if (jobs->size == 0) 
         printf("No jobs to display\n");
     else
         printList(jobs);
 }

void update_completed_jobs()
 {
     
     NodePtr traversal_node = jobs->head;
    if (traversal_node == NULL) return;
    
    do 
    {
        Jobs* jobs = (Jobs*)(traversal_node->obj);
        
        jobs->state = process_state(jobs->pid);
         if (jobs->state== DONE)
             jobs->status = status(jobs->pid);
     }
     while((traversal_node = traversal_node->next));
 }

int process_state(int pid)
 {
    int status;
    int child_pid = waitpid(pid, &status, WNOHANG);
    if (!child_pid && WIFEXITED(status))
    return ON;
    else
    return DONE;
 }

int exit_status(int pid)
 {
     int status;
     int child_pid = waitpid(pid, &status, WUNTRACED);

     if (child_pid == -1)
     return NORM;
     if (!child_pid && (WEXITSTATUS(status) || WIFSIGNALED(status))) // && WTERMSIG(status) <= SIGUNUSED && WTERMSIG(status) >= SIGHUP))
     return PROB;
     else
        return NORM;
}

void free_jobs()
 {
    freeList(jobs);
}

int status(int pid){
    int status;
    int child_pid = waitpid(pid, &status, WUNTRACED);
     if(child_pid == -1){
         return NORM;
     }
     if(!child_pid && WIFSIGNALED(status)){
         return PROB;
     }
     else{
         return NORM;
     }
}

void remove_completed_jobs()
{
     NodePtr traversal_node = jobs->head;
     if (traversal_node == NULL) return;
    
     while (traversal_node != NULL)
     {
         Jobs* jobs = (Jobs*)(traversal_node->obj);
        
         if (jobs->state== DONE)
         {
             NodePtr copy = traversal_node->next;
             freeNode(removeNode(jobsList, traversal_node), freeObject);
             traversal_node = copy;
        }
         else
         {
             traversal_node = traversal_node->next;
         }
     }
    
    if (jobs->size == 0) 
         jobID = 0;
 }

void display_update_jobs()
{
    update_completed_jobs();
    print_jobs();
    remove_completed_jobs();
}

int is_background_job(char** tokenized_command_and_args)
{
    
    int token_with_ampersand;
    for (token_with_ampersand = 0; token_with_ampersand < MAX_TOKENS && tokenized_command_and_args[token_with_ampersand]; ++token_with_ampersand);
    printf("token with ambersand: %d",token_with_ampersand);
    --token_with_ampersand;
    if (strstr(tokenized_command_and_args[token_with_ampersand], "&"))
        return token_with_ampersand;
    if (token_with_ampersand >= 1 && strstr(tokenized_command_and_args[token_with_ampersand-1], "&"))
        return token_with_ampersand;
    
    return -1;
}


void job_creation_printout(jobPtr job){

    printf("[%d] %d %s\n",job->job_num,job->pid,job->cmd);
}


int equals (const void * job1,const void *job2)
{
	int *id1 = (int *) job1;
	int *id2 = (int *) job2;
	return id1 == id2;
}

char* toString (const void* job)
{
	jobPtr objP = (jobPtr) job;
    temp = (char*)malloc(sizeof(char)*strlen(objP->cmd)+1+MAXPID+4);
    sprintf(temp, "[%d] %d %s  %s", objP->pid, objP->job_num, 
    objP->state == ON ? "Running" : "Done",
    objP->cmd);
    return temp;
}

void freeObject (void* job)
{
	jobPtr objP = (jobPtr) job;
	if (objP == NULL) return;
	free(objP->cmd);
	free(objP);
}

void remove_ampersand(char** command_and_args, int index_of_ampersand)
{
    char* token_with_ampersan = command_and_args[index_of_ampersand];
    
    if (strlen(token_with_ampersan) == 1)
    {
        command_and_args[index_of_ampersand] = (char*)0;
        return;
    }
    
    while (*token_with_ampersan)
    {
        if (*token_with_ampersan == '&')
        {
            *token_with_ampersan = (char*)0;
            return;
        }
        ++token_with_ampersan;
    }
}

char** get_tokenized_command(char * line){
	char *next;
    const char *delim = " ";
    int cnt=0;
    char **tokens;
    
    char* copy = (char*)malloc(strlen(line) * sizeof(char));
    strcpy(copy, line);
    
    tokens = (char**)malloc(MAX_TOKENS * sizeof(char*));

    next = strtok(copy, delim);
    while (next) {
        tokens[cnt] = (char *) malloc(strlen(next)+1);
        char * token = tokens[cnt++];
        strcpy(token, next);
        next =strtok(NULL, delim);
    }
    tokens[cnt] = (char *) 0;

    free(copy);
    return tokens;
}



