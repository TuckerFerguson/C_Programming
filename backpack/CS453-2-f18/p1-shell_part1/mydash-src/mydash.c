/*
  This program needs the file error.c and mydash.h to compile.
 */
#include "error.c"
#include "mydash.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>
#include    <sys/types.h>
#include    <sys/wait.h>
#include    <mydash.h>

/*Project Specs*/
#define MAXARGS 2048
#define MAXLINE 4096


//#added methods
char** chop_line_exec(const char *);
char* strncpy_safe(char *dst, const char *src, size_t len);
void emptyCommand(char*);


int main(void)
{
/*#### ADDED CODE ###
    char *line;
	char *prompt = "mydash>";
	using_history();
	while ((line=readline(prompt)))
			{
					printf("%s\n",line);
					add_history(line);
					free(line);
		    }
### END OF ADDED CODE####*/

    char    buf[MAXLINE];
    pid_t   pid;
    int     status;

    printf("%% ");  /* print prompt (printf requires %% to print %) */
    while (fgets(buf, MAXLINE, stdin) != NULL) {
        buf[strlen(buf) - 1] = '\0';    /* replace newline with null */

        if ( (pid = fork()) < 0)
            err_sys("fork error");

        else if (pid == 0) {        /* child */
            execlp(buf, buf, (char *) 0);
            err_ret("couldn't execute: %s", buf);
            exit(EXIT_FAILURE);
        }

/*###### ADDED CODE ######*/
		else if (pid == -1){
		fprintf(stderr,"Error, fork did not work");
		}
/*##### ADDED CODE ENDED ####*/

        /* parent */
        if ( (pid = waitpid(pid, &status, 0)) < 0)
            err_sys("waitpid error");
        printf("%% ");
    }
    exit(EXIT_SUCCESS);
}

/*#### NEW METHOD FOR TOKENIZING##
char** chop_line_exec(const char* line)
{
		char *token = NULL;
		int i = 0;
		char linecpy[MAXLINE];
		char **rval = malloc(MAXARGS);
		memset(rval,0,MAXARGS);
		strncpy_safe(linecpy,line,MAXLINE);

		token = strtok(linecpy," ");
		for(i=0; token && i<MAXARGS;i++){
				//fprintf(stderr,"got token %s\n",token);
				rval[i]=malloc(MAXLINE);
				strncpy_safe(rval[i],token,MAXLINE);
				token=strtok(NULL," ");
		}
		return rval;
}
*/
/* vim: set ts=4: */
