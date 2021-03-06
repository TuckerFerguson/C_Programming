#ifndef	__MYDASH_H
#define	__MYDASH_H

#include	<sys/types.h>	/* required for some of our prototypes */
#include	<stdio.h>		/* for convenience */
#include	<stdlib.h>		
#include	<sysexits.h>
#include	<string.h>
#include	<unistd.h>
#include "../../list/include/List.h"
#include "../../list/include/Node.h"
#include "job.h"


#define	MAXLINE	4096			/* max line length */

#define	FILE_MODE	(S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)
					/* default file access permissions for new files */
#define	DIR_MODE	(FILE_MODE | S_IXUSR | S_IXGRP | S_IXOTH)
					/* default permissions for new directories */
#define MAX_PIPE_LENGTH 4096
#define FAIL "FAIL"

/* prototypes for our own functions */

void	err_dump(const char *, ...);	/* {App misc_source} */
void	err_msg(const char *, ...);
void	err_quit(const char *, ...);
void	err_ret(const char *, ...);
void	err_sys(const char *, ...);


/* parsing constants and prototypes */
#define MAX_LENGTH 1024
#define MAX_TOKENS 2048
char **parseInput(char *s, char *delimiter, int *numTokens);
const char* git_version(void);

void display_jobs(void);
void remove_ampersand(char ** command_and_args, int index_of_ampersand);
char** get_command(char * line);
int is_background_job(char** tokenized_command_and_args);
void remove_ampersand(char** command_and_args, int index_of_ampersand);
void display_updated_jobs(void);
int status(int pid);
#endif	/* __MYDASH_H */