#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define MAX_LENGTH 2048
#define MAX_TOKENS 100

int main(int argc, char **argv) 
{
	while (1) {
		fprintf(stderr, "%s: running ps augx command.\n", argv[0]);
		system("ps augx > ps.log");

		sleep(2);
	}
	exit(0);
}

