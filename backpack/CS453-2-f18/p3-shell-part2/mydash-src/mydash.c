#include "error.h"
#include <stdlib.h>
#include <unistd.h>
#include "job.h"
#include "mydash.h"
#include "List.h"
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <mydash.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <signal.h>
#include <pwd.h>
#include <job.h>
#include    "../../list/include/Node.h"
#include    "../../list/include/List.h"

//*******************************************
// @Author Tucker Ferguson 
// @Date 9/17/18
//*******************************************

#define MAXARGS 3000
#define MAXLINE 4096
void execute(char *);
void empty(char *);
void version(void);
void change_my_dir(char *);
void change(void);
void print_jobs(void);
void init_job_manager(void);
void update_completed_jobs(void);
void remove_completed_jobs(void);
void job_creation_printout(jobPtr job);
void free_jobs(void);
int execCmd(char *, char **);
void emptyChange(void);
void display_update_jobs(void);
char **chop_line_exec(const char *);
char *strncpy_safe(char *dst, const char *src, size_t len);
//new 
// Boolean start_background_job(char*, char**, int);
// Boolean start_job(char*, char**);
// void print_jobs();
// void init_job_manager();
// void log_background_job(int, char*);
// void update_completed_jobs();
// void remove_completed_jobs();
// int process_state(int);
// void free_jobs();
// int exit_status(int);
//



int jobID;

ListPtr jobs;
ListPtr jobsList;
struct list* activeJobs;


//new variables for background jobs
// uid_t uid = getuid();
// pid_t processID;
// struct pass* pwuid = getpwuid(uid);
// int backgroundJob;
// int nextJob = 1;

// processID = getpgrp();

// if((setpgid(0,0)) < 0){
// erry_sys("error setting pgid");
// }

// signal(SIGTTOU, SIG_IGN);
// signal(SIGINT, SIG_IGN);
// signal(SIGTSTP, SIG_IGN);

// jobs = createList(0,NULL,NULL);


//

int main(void)
{
    char *prompt = getenv("DASH_PROMPT");
    char *line;
    char lineCopy[MAXLINE];
    using_history();


//new 
    init_job_manager();

    while ((line = readline(prompt)))
    {
        if (strlen(line) == 0)
        {   
            //new
            free(line);
            //display_update_jobs();
            //
            continue;
        }

        //char** tokenized_command_and_args = get_tokenized_command(line);



        add_history(line);
        strncpy(lineCopy, line, MAXLINE);
        char *token = strtok(lineCopy, " ");
        if (strcmp("exit", token) == 0)
        {
            exit(0);
        }
        else if (strcmp("cd", token) == 0)
        {
            char *token = strtok(line, " ");
            change_my_dir(token);
        }
        else if (strcmp("-v", token) == 0)
        {
            version();
        }
        else if (strcmp("history", token)==0)
        {
        HIST_ENTRY** history = history_list();
		if (!history)
		{
		return 0;
		}
		int i = 0;
		for (; history[i] ; ++i)
		  {
		   printf("[%d] %s\n", i + history_base, history[i]->line);
		  }
		return 0;
        }
        else
        {
            execute(line);
        }
        free(line);
    }

    exit(0);
}
//method for chop line exec
char *strncpy_safe(char *dst, const char *src, size_t len)
{
    char *rval = NULL;
    rval = strncpy(dst, src, len);
    rval[len - 1] = '\0';
    return rval;
}

//this is code for chopping lines
char **chop_line_exec(const char *line)
{
    char *token = NULL;
    int i = 0;
    char linecpy[MAXLINE];
    char **rval = malloc(MAXARGS);
    memset(rval, 0, MAXARGS);
    strncpy_safe(linecpy, line, MAXLINE);
    token = strtok(linecpy, " ");
    for (i = 0; token && i < MAXARGS; i++)
    {
        rval[i] = malloc(MAXLINE);
        strncpy_safe(rval[i], token, MAXLINE);
        token = strtok(NULL, " ");
    }

    return rval;
}
//executes commands using execvp
void execute(char *token)
{
    pid_t pid;
    pid = fork();
    int status;
    if (pid < 0)
    {
        err_sys("fork error");
    }
    else if (pid == -1)
    {
        fprintf(stderr, "error no good");
    }else if(pid == 0){
         if (index_of_ampersand >= 0)
            {
                start_background_job(line, tokenized_command_and_args, index_of_ampersand);
                write(error_pipe[1], FAIL, strlen(FAIL)+1);
                //give write time to propagate
                usleep(1000);
            }
            else
            {
                start_job(line, tokenized_command_and_args);
            }
//            free_command_and_Line(line, tokenized_command_and_args);
            exit(EXIT_FAILURE);
        }
    }
    else if (pid == 0)
    { 
        char **commandArgs = (char **)(MAXARGS * sizeof(char));
        const char *bufpointer = token;
        commandArgs = chop_line_exec(bufpointer);
        execvp(commandArgs[0], commandArgs);
        free(commandArgs);
        kill(getpid(), 1);
    }
    if (getppid() > 0)
    {
        waitpid(-1, &status, 0);
    }
}
//Handles valid arguments passed in with
void change()
{
    char *cur_dir = getcwd(NULL, 0);
    free(cur_dir);
}
//Handles no arguments passed in with cd
void emptyChange()
{
    char *homedir = getenv("HOME");
    if (homedir == NULL)
    {
        uid_t uid = getuid();
        struct passwd *pw = getpwuid(uid);
        char *homedir = pw->pw_dir;
        chdir(homedir);
    }
    else
    {
        chdir(homedir);
    }
}
//Changes directory handles empty args as well using change()/emptyChange()
void change_my_dir(char *token)
{
    token = strtok(NULL, " ");
    int success = chdir(token);
    if (success == 0)
    {
        change();
    }
    else
    {
        emptyChange();
    }
}
//Prints version and then exits
void version()
{
    const char *v = git_version();
    printf("mydash: Version 1: Revision %s (author: User TuckerFerguson@onyx)\n", v);
    exit(0);
}


/* vim: set ts=4: */
