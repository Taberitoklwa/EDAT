CC=gcc
CFLAGS =-Wall -pedantic -ansi -g 

.PHONY: clean

all: p1_e1

#################################################

p1_e1: maze.o p1_e1.o
	$(CC) -o $@ $^ 

#################################################
maze.o: maze.c maze.h types.h
	$(CC) $(CFLAGS) -c $<

p1_e1.o: p1_e1.c maze.h
	$(CC) $(CFLAGS) -c $<

#################################################

clean: 
	@rm -f maze.o p1_e1.o p1_e1