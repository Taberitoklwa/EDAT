CC=gcc
CFLAGS =-Wall -pedantic -g 
CLIB= -lscreen -L.

.PHONY: clean

all: p1_e1

#################################################

p1_e1: maze.o p1_e1.o
	$(CC) -o $@ $^ $(CLIB)

#################################################
maze.o: maze.c maze.h types.h
	$(CC) $(CFLAGS) $<

p1_e1.o: p1_e1.c maze.h
	$(CC) $(CFLAGS) $<

#################################################

clean: 
	@rm -f maze.o p1_e1.o p1_e1