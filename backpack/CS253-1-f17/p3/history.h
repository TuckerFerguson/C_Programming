#ifndef __MYHEADER_H
#define __MYHEADER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct cmd{
	char * cmd; // bit of memory that stores string
         //more code will be added here in future (part 3)
};

void init_history();

void add_history(char *);

void clear_history();

void print_history();

#endif /* __MYHEADER_H */