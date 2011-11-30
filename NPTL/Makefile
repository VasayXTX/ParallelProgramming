#Type of compiler
CC = gcc

#Options for development
CFLAGS = -D_REENTRANT -O0 -g -Wall

#Options for production
#CFLAGS = -D_REENTRANT -O -Wall

LFLAGS = -lpthread

problem1: problem1.o
	$(CC) $(CFLAGS) problem1.o -o problem1 $(LFLAGS)

problem2: problem2.o
	$(CC) $(CFLAGS) problem2.o -o problem2 $(LFLAGS)

problem3: problem3.o
	$(CC) $(CFLAGS) problem3.o -o problem3 $(LFLAGS)

.c.o: pthread_checker.h
	$(CC) $(CFLAGS) -c $<

clean:
	rm -rf *.o problem1 problem2 problem3
	@echo Cleaning copmplete

