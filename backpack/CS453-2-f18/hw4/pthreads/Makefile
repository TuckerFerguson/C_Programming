
DEBUG=
CC=gcc
CFLAGS=-g -O2 -std=gnu89 -Wall -Wpointer-arith -Wstrict-prototypes -I. $(DEBUG)
LFLAGS=-lpthread

OBJS=FileAccess.o testfileAccess.o 

all: testfileAccess 

testfileAccess: testfileAccess.o FileAccess.o $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS) $(LFLAGS)
	

clean:
	/bin/rm -f *.o core a.out $(OBJS) testfileAccess
