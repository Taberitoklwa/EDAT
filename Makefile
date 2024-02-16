CC=gcc
CFLAGS =-Wall -pedantic -g 

.PHONY: clean

all: p1_e1 p1_e2

#################################################

p1_e1: maze.o p1_e1.o
	$(CC) -o $@ $^ 

p1_e2: maze.o p1_e2.o
	$(CC) -o $@ $^ 

#################################################
maze.o: maze.c maze.h types.h
	$(CC) $(CFLAGS) -c $<

p1_e1.o: p1_e1.c maze.h
	$(CC) $(CFLAGS) -c $<

p1_e2.o: p1_e2.c maze.h
	$(CC) $(CFLAGS) -c $<

#################################################

clean: 
	@echo "Cleaning objects..."
	@rm -f maze.o p1_e1.o p1_e1 p1_e2.o p1_e2