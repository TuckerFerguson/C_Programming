#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#define MAXLINE 4096
void printError();
void changeDir();

int main (int argc, char *argv[])
{
	char buff[MAXLINE];
	char buffCopy[MAXLINE];
	fprintf(stderr,"$");
	while (fgets(buff, MAXLINE, stdin) != NULL)
	{
		int back = strlen(buff);
		back--;
		buff[back] = '\0';
		strncpy(buffCopy, buff, MAXLINE);
		char *token = strtok(buffCopy, " ");
		if(strcmp("exit", token) == 0)
		{
			exit(0);
		}
		if (strcmp("cd", token) == 0)
		{
			token = strtok(NULL," ");
			int SUCCESS = chdir(token);
			if (SUCCESS == 0)
			{
				changeDir();
			}
			else
			{
				printError();
			}
		}
		else
		{
			char* token = strtok(buff," ");
			int number = 0;
			while (token != NULL)
			{
				printf("[%d] %s\n", number, token);
				token = strtok (NULL, " ");
				number++;
			}
		}
		fprintf(stderr,"$");
	}
	return EXIT_SUCCESS;

}

void printError(char *oops){
	printf("error: ");
	printf(oops);
	printf(" does not exist\n");
}
void changeDir(char *cd){
	char* cur_dir = getcwd(NULL, 0);
	printf("%s\n", cur_dir);
	free(cur_dir);
}


// dont copy shanes solution (more advance)

//for history.h
//void init_history(); //complete
//void add_history(struct cmd* c, char* s ); //might not be right lulz
//void clear_history(); //complete
//void print_history(); //complete

//shanes help solutions
/**
#ifndef _History_H
#define _History_H#define MAXLINE 4096

struct cmd{
		void *pid
		char *cmd;
		char **argv;
		};
		struct history{
			unsigned int capacity;
			unsigned int offset;
			struct cmd ***entries;
			};
			void ini_history(struct history *, unsigned int capactiy);

			void add_history(struct history *, char *cmd);
			
			void print_history(struct history *);
			void clear_history(struct histroy *);

			#endif /* _History_H */
	
