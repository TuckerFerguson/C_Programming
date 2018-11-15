#include "job.h"
#include <string.h>
#include <stdio.h>
#include "mydash.h"

#include "../../list/include/List.h"

//struct job* jobPtr;
char *temp;
char* isAmpersand(char* cmd)
{	
	//printf("cmd for ampersand %s\n",cmd);
	char* copy = malloc(strlen(cmd) + 1);
	strncpy(copy,cmd,strlen(cmd) + 1);
	copy = strchr(copy,'&');
	return copy;
}

// char* handle_ampersand(char* cmd)
// {
// 	int i = 0;
// 	char* copy = malloc(strlen(cmd) + 1);
// 	strncpy(copy,cmd,strlen(cmd+1));
// 	//printf("copy[count] = %s\n",copy[count]);
// 	//if(strcmp(cmd,"&"));
// 	//{ return NULL;}

// 	while(i < strlen(cmd) + 1) 
// 	{
// 		if(cmd[i] != '&')
// 		{
// 			copy[i] = cmd[i];
// 		}
// 		i++;
// 	}
// 	return copy;
// }

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
    sprintf(temp, "%d %d %s %s \"%s\"", objP->pid, objP->job_num, 
    objP->state == ON ? "Running" : "Completed",
    objP->status == NORM ? "Normal" : "problem",
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
    char* token_with_ampersand = command_and_args[index_of_ampersand];
    
    if (strlen(token_with_ampersand) == 1)
    {
        command_and_args[index_of_ampersand] = (char*)0;
        return;
    }
    
    while (*token_with_ampersand)
    {
        if (*token_with_ampersand == '&')
        {
            *token_with_ampersand = (char*)0;
            return;
        }
        ++token_with_ampersand;
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
    tokens[cnt] = (char *) 0; /* make the field array be null-terminated */

    free(copy);
    return tokens;
}

int is_background_job(char** tokenized_command_and_args)
{
    //two cases
    //i) it is conjoined with the final command
    //ii) it is all alone as the final arugment
    
    int token_with_ampersand;
    for (token_with_ampersand = 0; token_with_ampersand < MAX_TOKENS && tokenized_command_and_args[token_with_ampersand]; ++token_with_ampersand);
    
    --token_with_ampersand;
    if (strstr(tokenized_command_and_args[token_with_ampersand], "&"))
        return token_with_ampersand;
    if (token_with_ampersand >= 1 && strstr(tokenized_command_and_args[token_with_ampersand-1], "&"))
        return token_with_ampersand;
    
    return -1;
}

