#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#define MAX_LENGTH 2048
#define MAX_TOKENS 100

//author: Tucker Ferguson

int multiT, totalT;
double percent;
void warning1(void);
void usage1(void);
int main(int argc, char **argv){
//Ensures that user enters proper command line arguments
	if (argc != 2){
		usage1();
	}
//Ensures that the time interval is greater than or equal to one
	else if(atoi(argv[1]) < 1){
		warning1();
	}
	else{
	fprintf(stderr,"%s: Using a sleep time of %s seconds.\n", argv[0], argv[1]);
	while(1){
	multiT = 0;
	totalT = 0;
	percent = 0;
	system("ps augx > ps.log");

        FILE *fPoint;
	if((fPoint = fopen("ps.log", "r")) == NULL){
	 printf("File not found");
	 exit(1);
	}
	char temp[MAX_LENGTH];
//This scans the log file for strings "R...l" and "S...l"
	while(fscanf(fPoint, " %1000s", temp) == 1){
		if(temp[0] == 'R' && temp[strlen(temp) - 1] == 'l'){
		multiT++;
		}else if(temp[0]  == 'S' && temp[strlen(temp) - 1] == 'l'){
		multiT++;
		}
	}
//Points back to start of file input string for scanner
	rewind(fPoint);
//Gets value of total processes
	while(fgets(temp,30000,fPoint)!= NULL){
		totalT++;
	}
	percent = 100.0 * multiT / totalT;
	fprintf(stdout, "%s: %d/%d processes are multithreaded. [%.2f%c]\n",argv[0],multiT,totalT,percent,'%');
		sleep(atoi(argv[1]));
	}
		exit(0);
	}
		return 0;
}
void usage1(){
        printf("Usage: ps-logger <sleep interval(seconds)>\n");
}

void warning1(){
	printf("ps-logger:Specified too small an interval. Must be at least 1 second.\n");
}

