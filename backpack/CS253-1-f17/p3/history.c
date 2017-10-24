#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_HISTORY 10000 //arbitrary number
static struct{
	int loc;
	struct cmd **structArray;
}
history;

void init_history(){
	int i = 0;
	history.loc = 0;
	history.structArray = (struct cmd **)malloc(sizeof(char *) * MAX_HISTORY); 
	for (i= 0 ; i < MAX_HISTORY; ++i){
	  history.structArray[i] = NULL;
	}
	
}

void add_history( char* val){
	if (history.loc >= MAX_HISTORY){
	 return; 
	}
	struct cmd* cmdS = (struct cmd*)malloc(sizeof(struct cmd));
	cmdS->cmd = (char *) malloc(strlen(val) +1);
	strcpy(cmdS->cmd, val);
	history.structArray[history.loc] = cmdS;
	history.loc++;
	
}

void clear_history(){
  struct cmd ** temporary = history.structArray;
  while(*temporary){
	struct cmd *clean = *temporary;
	free(clean);
	free(*temporary);
	temporary++;
  }
   free(history.structArray);
}


void print_history(){
  int i = 0;
	for(i=0;i<history.loc;i++){
	  printf("%d",i+1);
	  //white space to ensure proper output
	  printf(" ");
	  //prints out strings stored in struct 
	  printf("%s\n", history.structArray[i]->cmd);
	}
}