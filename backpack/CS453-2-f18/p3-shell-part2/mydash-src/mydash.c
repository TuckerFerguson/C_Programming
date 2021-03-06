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
#include "../../list/include/Node.h"
#include "../../list/include/List.h"

//*******************************************
// @Author Tucker Ferguson
// @Date 9/17/18
//*******************************************

#define MAXARGS 3000
#define MAXLINE 4096
int index_of_ampersand;
char *sanitize(char *token);
void execute(char *);
void empty(char *);
void version(void);
void change_my_dir(char *);
void change(void);
void print_jobs(void);
void init_job(void);
void update_completed_jobs(void);
void remove_completed_jobs(void);
void job_creation_printout(jobPtr job);
void free_jobs(void);
int execCmd(char **);
void emptyChange(void);
void display_jobs(void);
char **chop_line_exec(const char *);
char *strncpy_safe(char *dst, const char *src, size_t len);
int error_pipe[2];
int state;
int state;
int jobID;
char child_status[MAXLINE];
ListPtr jobs;
ListPtr jobsList;
struct list *activeJobs;

int main(void)
{
    char *prompt = getenv("DASH_PROMPT");
    char *line;
    char lineCopy[MAXLINE];
    using_history();
    if (!(prompt = getenv("DASH_PROMPT")))
    {
        prompt = "mydash> ";
    }

    //new
    init_job();

    while ((line = readline(prompt)))
    {
        if (strlen(line) == 0)
        {
            free(line);
            display_jobs();
            continue;
        }

        add_history(line);
        strncpy(lineCopy, line, MAXLINE);
        char *token = strtok(lineCopy, " ");
        if (strcmp("exit", token) == 0)
        {
            exit(0);
            free_jobs();
            kill(getpid(), SIGKILL);
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
        else if (strcmp("history", token) == 0)
        {
            HIST_ENTRY **history = history_list();
            if (!history)
            {
                return 0;
            }
            int i = 0;
            for (; history[i]; ++i)
            {
                printf("[%d] %s\n", i + history_base, history[i]->line);
            }
            return 0;
        }
        else if (strcmp("jobs", token) == 0)
        {
            display_jobs();
        }
        else
        {
            pid_t pid;
            pid = fork();
            //int status;
            if (pid < 0)
            {
                err_sys("fork error");
            }
            else if (pid == -1)
            {
                fprintf(stderr, "error no good");
            }
            else if (pid == 0)
            {
                char **commandArgs = (char **)(MAXARGS * sizeof(char));
                // const char *bufpointer = token;
                commandArgs = get_command(line);
                index_of_ampersand = is_background_job(commandArgs);
                close(error_pipe[0]);
                if (index_of_ampersand >= 0)
                {
                    start_background_job(commandArgs, index_of_ampersand);
                    write(error_pipe[1], FAIL, strlen(FAIL) + 1);
                    usleep(1000);
                }
                else
                {
                    start_job(commandArgs);
                }
                exit(EXIT_FAILURE);
            }
            if (index_of_ampersand < 0)
            {
                pid = waitpid(pid, &state, 0);
            }
            else
            {
                sleep(1);
                if (!strstr(child_status, FAIL))
                    log_background_job(pid, line);

                int i;
                for (i = 0; i < MAXLINE; i++)
                    child_status[i] = 0;
            }
        }
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

char **get_command(char *line)
{
    char *next;
    const char *delim = " ";
    int cnt = 0;
    char **tokens;

    char *copy = (char *)malloc(strlen(line) * sizeof(char));
    strcpy(copy, line);

    tokens = (char **)malloc(MAXARGS * sizeof(char *));

    next = strtok(copy, delim);
    while (next)
    {
        tokens[cnt] = (char *)malloc(strlen(next) + 1);
        char *token = tokens[cnt++];
        strcpy(sanitize(token), next);
        next = strtok(NULL, delim);
    }
    tokens[cnt] = (char *)0;

    free(copy);
    return tokens;
}

char *sanitize(char *token)
{
    return token;
}

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
    exit(1);
}

/* vim: set ts=4: */
