#build the grader from the file test.c

CC=gcc
CFLAGS=-Wall -g -I../include 

grader: test-threads.c
	$(CC) $(CFLAGS) -o $@ $^  -L../lib/ -lring -lpthread

clean:
	/bin/rm -f *.o grader
