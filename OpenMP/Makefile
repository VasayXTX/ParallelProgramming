#Type of compiler
CC = gcc

#Options for development
#CFLAGS = -fopenmp -g -Wall

#Options for production
CFLAGS = -fopenmp -O

problem1: problem1.c
	$(CC) $(CFLAGS) problem1.c -o problem1

problem2: problem2.c quicksort.h quicksort.c
	$(CC) $(CFLAGS) problem2.c quicksort.c -o problem2

problem3: problem3.c quicksort.h mergesort.h quicksort.c mergesort.c
	$(CC) $(CFLAGS) problem3.c quicksort.c mergesort.c -o problem3

clean:
	-rm problem1 problem2
