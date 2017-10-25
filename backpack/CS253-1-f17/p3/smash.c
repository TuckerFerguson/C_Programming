#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "history.h"
#include "history.c"
#include <stdbool.h>

#define MAXLINE 4096

//smash_get_input(char *);
void empty(char*);
void oops(char*);
void change_my_dir(char*);
void printToken(char*);
void change();
char  buffCopy[MAXLINE];

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
			exit(0);
		}
		else if (strcmp("cd", token) == 0) {
			char* token = strtok(buff," ");		  
			change_my_dir(token);
		}
		else if(strcmp("history",token) == 0) {
			//prints history
			print_history();
		}
		else {
			//or else continues printing tokens
			printToken(token);
		}
		//makes sure $ symbol starts each new line
		fprintf(stderr,"$");	
	  }
	//clears history after commands have stopped being entered
	clear_history();
	return EXIT_SUCCESS;
  
}

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

void oops(char *token){
		printf("error: ");
		printf(token);
		printf(" does not exist\n");
}
void change(){
		char* cur_dir = getcwd(NULL, 0);
		printf("%s\n", cur_dir);  
		free(cur_dir);
}

void printToken(char* token){
	int count = 0;
	while (token != NULL){
		printf ("[%d] %s\n",count, token);
		token = strtok (NULL, " ");
		count++;
	}
	count = 0;

}