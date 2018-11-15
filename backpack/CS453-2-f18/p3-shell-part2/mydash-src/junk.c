#include    <sys/types.h>
#include    <sys/wait.h>
#include    <mydash.h>
#include    <readline/readline.h>
#include    <readline/history.h>
#include    <signal.h>
#include    <stdio.h>
#include    <pwd.h>

#include    "../../list/include/Node.h"
#include    "../../list/include/List.h"

int tokenCount;
char *line;
int lineLength = MAXLINE;
struct list* jobs;
struct list* runningJobs;

/**
* Main method, parses arguments
* @param argc and argv, arg count and value of args
* returns 0 on successful execution
**/
int main(int argc, char** argv){
    //TODO: print job segfault

    char* username = generatePrompt();

    uid_t uid = getuid();
	pid_t shell_pg; 
	struct passwd* pwuid = getpwuid(uid);
	int start_in_bg; /* flag variable for background jobs */
	int next_job_id = 1;
	

    git_args(argc, argv); //checks for git version arg
    char *buffer;
    buffer = (char*)malloc(lineLength);

    //Readline library history init call
    using_history();

    //gets shell process group
    shell_pg = getpgrp();

	if((setpgid(0, 0)) < 0)
		err_sys("Could not set pgid");

    //ignore writes out since it is not foreground
    signal(SIGTTOU, SIG_IGN);	
    //interrupt
	signal(SIGINT, SIG_IGN);
    //keyboard sigstop, can be ignored
	signal(SIGTSTP, SIG_IGN);
    jobs = createList(0, NULL, NULL);

    while((buffer = readline(username)) != NULL){
        if(!emptyInput(buffer)){ //check if there is a command input
            add_history(buffer);
            parse(buffer, &start_in_bg, argv);
			 if((strcmp(argv[0], "Exit") == 0) || (strcmp(argv[0], "exit") == 0) || (strcmp(argv[0], "cd") == 0) || (strcmp(argv[0], "history") == 0) || (strcmp(argv[0], "jobs") == 0) ){
                runCommonCommand(buffer, argv, jobs, runningJobs, &start_in_bg, pwuid, shell_pg, buffer);
             }
            else if(!(strcmp(argv[0], "cd") == 0) && !(strcmp(argv[0], "exit") == 0) && !(strcmp(argv[0], "Exit") == 0)){
                run(argv, buffer, jobs, runningJobs, &start_in_bg, &next_job_id, shell_pg);
            }
            else{
                while(argv[0] != NULL){ //removes spaces and tokenizes
                    argv[0] = strtok(NULL, " ");
                }
            }
            //add to history and free memory
            signal(SIGTTOU, SIG_IGN);
            free(buffer);
        }else{
        signal(SIGTTOU, SIG_IGN);
        //Implement this
        //print_finished_jobs(jobs, &next_job_id);
        free(buffer);
        }
    }
    return 0;
}

void runCommonCommand(char* input, char** argv, struct list* jobs, struct list* runningJobs, int* next_job_id, struct passwd* pwuid, pid_t shell_pg, char* buffer){
    char dir[1024];
    if((strcmp(input, "Exit") == 0) || ((strcmp(input, "exit")) == 0)){ //exit command
                //runExit(jobs, runningJobs, buffer);
        while(getSize(jobs)>0){
            removeRear(jobs);
        }
        while(getSize(jobs)>0){
            removeRear(runningJobs);
        }
        freeList(jobs);
        free(buffer);
        exit(0);
    }else if(strcmp(input, "cd") == 0 ){ //change directory command
        changeDir(argv, dir, pwuid);
    }else if(strcmp(input, "history") == 0 ){ //show history
        print_history();
    }else if(strcmp(input, "jobs") == 0 ){ //show jobs
        printList(jobs);
    }
}
/**
* generatePrompt - creates the dash prompt for the user
* @return the concatenated string to be put on the terminal
*/
char* generatePrompt(void){
    char* ret = getenv("USER"); //creates mydash prompt 
    char* host = getenv("HOSTNAME");
    host = strtok(host, ".");
    strcat(ret, "@"); //concatenates username and hostname
    strcat(ret, host);
    char* dash_prompt = getenv("DASH_PROMPT"); //custom dash prompt
    if(dash_prompt != NULL)
        strcat(ret, dash_prompt);
    else{
        strcat(ret, " > ");
    }
    return ret;
}

/**
* emptyInput checks to see if the arg is empty or not
* @param in, the input to command line
* @returns 0 or 1 based on length of in
**/
int emptyInput(char* in){
    int size = strlen(in);
    if(size == 0){ //empty
        return 1;
    }
    else{
        return 0;
    }
}

void print_history(void)
{
	HISTORY_STATE* myhist = history_get_history_state();
	HIST_ENTRY **hist = history_list();
	int i;
	for(i = 0; i < myhist->length; i++)
		printf("%d %s\n", i, hist[i]->line);
}

/**
* git_args checks for -v flag and retrieves git version
* @param argc and argv, the count and value of arguments
**/
void git_args(int argc, char** argv)
{
    if(argc != 1) {
        if(strcmp(argv[1], "-v") != 0) { //anything besides -v
            printf("Usage: ./mydash OR ./mydash -v\n");
            exit(EXIT_SUCCESS);
        }
        else { //-v flag found
            const char* versionInfo = git_version(); //finds git version
            printf("mydash: Version 1: Revision %s (author: Noah Rudin noahrudin994@u.boisestate.edu)\n", versionInfo);
            exit(EXIT_SUCCESS);
        }
    }
}

/**
* parse, tokenizes the arguments
* @param in, string input - max, MAXLINE - args[], array of arguments
**/
void parse(char* in, int* start_in_bg, char* args[]){
    *start_in_bg = check_ampersand(in);
    args[0] = strtok(in, " \t\n"); //tokenize input

    int x = 1;
    while((args[x] = strtok(NULL, " \t\n")) != NULL && x < MAX_ARGS) 
        x++; //checks for maxline and null
}

/**
* run, creates process for given command
* @param argv, the command line input
**/
void run(char **argv, char* input, struct list* jobs, struct list* runningJobs, int* start_in_bg, int* next_id, pid_t shell_pg)
{   
    pid_t pid; //new process
    int time;
    struct job* new_job = (struct job*)malloc(sizeof(struct job));

    
    char* parsedCmd = input;

	new_job->cmd = parsedCmd;
	new_job->id = *next_id;

	new_job->status = -1;
	new_job->run_in_bg = *start_in_bg;
    printf("%s\n", new_job->cmd);

    if((new_job->pid = fork()) < 0)
		err_sys("fork error");
	else if(new_job->pid == 0) {
		/* child */
		setpgid(0,0);
		new_job->pgid = getpgid(new_job->pid);

		signal(SIGINT, SIG_DFL);
		signal(SIGTSTP, SIG_DFL);
		
		free(new_job);
		execvp(argv[0], argv);
		err_ret("couldn't execute: %s", input);
		exit(EXIT_FAILURE);
	}
	
	/* parent */

	if((setpgid(new_job->pid, new_job->pid)) != 0)
		err_sys("setpgid error\n");
	
	new_job->pgid = getpgid(new_job->pid);
    NodePtr node = createNode(new_job);
	addAtRear(jobs, node);
    addAtRear(runningJobs, node);
	*next_id = *next_id + 1;
	
	if(new_job->run_in_bg) {
		printf("[%d] %d\t%s\n", new_job->id, new_job->pid, new_job->cmd);
		waitpid(new_job->id, &new_job->status, WNOHANG);
	}
	else {

		tcsetpgrp(STDIN_FILENO, new_job->pid); 
		if((waitpid(new_job->pid, &new_job->status, WUNTRACED)) < 0) {
			free(new_job->cmd);
			free(new_job);
		}
		tcsetpgrp(STDIN_FILENO, shell_pg); 
        //TODO
        //removeRear(runningJobs);
        //printList(runningJobs);
		//print_if_stopped(jobs, jobs->size - 1);

	}
        
}


int check_ampersand(char* input)
{
	int i = 0;
	int length = strlen(input);

	if(strchr(input, '&') != NULL) {
		while(i < length) {
			if(input[i] == '&') {
				input[i] = '\0';
				break;
			}
			i++;
		}
		trim(input);
		return 1;
	}
	return 0;
}

void trim(char* str)
{
	int i = strlen(str) - 1;
	while(isspace(str[i])) {
		str[i] = '\0';
		i--;
	}
}


/**
* changeDir, executes cd command
* @param argv and dir, arg value and desired folder
**/
void changeDir(char **argv, char* dir, struct passwd* pwuid)
{
    char* homedir = pwuid->pw_dir;

	if(argv[1] == NULL || strcmp(argv[1], "~") == 0) {
		chdir(homedir);
		getcwd(dir, 1024);
		printf("%s\n", dir);
	}	
	else {
		if((chdir(argv[1])) != 0)
			printf("%s: No such file or directory\n", argv[1]);
		else {
			getcwd(dir, 1024);
			//printf("%s\n", dir);
		}
	}
}


void freeObject(void *obj)
{
    free(obj);
}

void signal_job(int signo)
{
	kill(getpid(), signo);
}