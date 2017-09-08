CC = gcc
CFLAGS = -Wall -g -MMD
PROGS = main.c f1.c f2.c f3.c

all: myprog

myprog: $(PROGS)
	$(CC) $(CFLAGS) $^ -o $@
-include *.d
clean:
	rm -f *.o myprog
	rm -f *.d myprog
