#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include "history.h"
#include "history.c"
#include <stdbool.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAXARGS 2048
#define MAXLINE 4096

void empty(char*);
void oops(char*);
void change_my_dir(char*);
void printToken(char*);
void change();
char** chop_line_exec(const char *);
char* strncpy_safe(char *dst, const char *src, size_t len);
char  buffCopy[MAXLINE];
int status;
int main(void)
{
	init_history();
	char  buff[MAXLINE];
	fprintf(stderr,"$");
	
	while (fgets(buff, MAXLINE, stdin) != NULL) {

		int last = strlen(buff);
		last--;
		buff[last] = '\0';
		if(strlen(buff) == 0){
			fprintf(stderr,"$");
			continue;
		}
		strncpy(buffCopy, buff, MAXLINE);
		char *token = strtok(buffCopy, " ");
		add_history(buff);
		//smash_get_input(buff);
		if(strcmp("", token)==0){
			fprintf(stderr,"$");
		}
		else if(strcmp("exit", token) == 0){
		//exits
		clear_history(buff);
			exit(0);
		}
		else if (strcmp("cd", token) == 0) {
			//changes directory
			char* token = strtok(buff," ");		  
			change_my_dir(token);
		}
		else if(strcmp("history",token) == 0) {
			//prints history
			print_history();
		}
		else {
			//or else continues printing tokens
			pid_t pid;
			pid = fork();
	if(pid == -1){
		//fork did not work properly
		fprintf(stderr,"error, es no bueno");
	}
	if(pid == 0){
		const char* s = getenv("CHAOS_MONKEY_DISABLE");
	if(s == NULL){
		srand((unsigned int)time(NULL));
	if(rand() % 100 <= 25){
		fprintf(stderr,"The monkey strikes again!!\n");
		exit(0);
	}
}

	char ** commandArgs = (char**)(MAXARGS*sizeof(char));
	const char* buffpointer = buff;
	commandArgs = chop_line_exec(buffpointer);
	execvp(commandArgs[0], commandArgs);
	free (commandArgs);
	kill(getpid(), 1);
}
	if(getppid() > 0){
		waitpid(-1, &status, 0);
}

		}
		//makes sure $ symbol starts each new line
		fprintf(stderr,"$");	
	  }
	//clears history after commands have stopped being entered
	clear_history();
	return EXIT_SUCCESS;
  
}
char* strncpy_safe(char *dst, const char *src, size_t len)
{
	char *rval=NULL;
	rval=strncpy(dst,src,len);
	rval[len-1]='\0';
	return rval;
}
/**
 * Takes a line and splits on spaces. Returns an array of each token
 * taken from the line.  The returned array will be formatted in the
 * correct format for the exec family of functions (ie terminated by a
 * NULL ptr) NOTE: Caller is responsible for freeing memory
 */
char** chop_line_exec(const char* line)
{
	char *token = NULL;
	int i=0;
	char linecpy[MAXLINE];
	//Allocate an array big enough to handle the max number of
	//args. If we have a line with more than MAXARGS we will
	//ignore everything after MAXARGS length.
	char **rval = malloc(MAXARGS);
	memset(rval,0,MAXARGS);
	//copy our arg because strtok destroys the line.
	strncpy_safe(linecpy,line,MAXLINE);

	//Now lets grab all the tokens
	token = strtok(linecpy," ");
	for(i=0;token && i<MAXARGS;i++){
		//fprintf(stderr,"got token %s\n",token);
		rval[i]=malloc(MAXLINE);
		strncpy_safe(rval[i],token,MAXLINE);
		token=strtok(NULL," ");
	}

	return rval;
}
//changes the directory if cd is entered in command line
void change_my_dir(char* token){
	token = strtok(NULL," ");
	int success = chdir(token);
	if (success == 0)
	{	
		change();
	}
	else
	{
		oops(token);
	}

}
//prints error if token passed in is not whats expected
void oops(char *token){
		printf("error: ");
		printf(token);
		printf(" does not exist\n");
}
//changes directory
void change(){
		char* cur_dir = getcwd(NULL, 0);
		printf("%s\n", cur_dir);  
		free(cur_dir);
}
//prints token
void printToken(char* token){
	int count = 0;
	while (token != NULL){
		printf ("[%d] %s\n",count, token);
		token = strtok (NULL, " ");
		count++;
	}
	count = 0;

}