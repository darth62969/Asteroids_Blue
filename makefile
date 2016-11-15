# Makefile to build introgl example 
#
# Andrew J. Pounds, Ph.D.
# Departments of Chemistry and Computer Science
# Mercer University
# Fall 2016 
#
# Modified for use in: The Blue Team's Asteroids 
# Modified by: Blue Squad
#

CC = g++ 
CFLAGS = 
COPTFLAGS = -O3 
LIBFLAGS = -lglut -lGLU -lGL
HEADERS = src/headers.h src/structs.h src/globals.h src/prototypes.h
OBJS = main.o asteroid.o ship.o bullets.o transformer.o

# Independent Targets - first is executable, second is object

Asteroids : $(OBJS) $(HEADERS)
	$(CC) -o bin/Asteroids $(OBJS) $(LIBFLAGS)

main.o : src/main.cpp $(HEADERS)
	$(CC) $(CFLAGS) $(COPTFLAGS) -c src/main.cpp

asteroid.o: src/asteroid.cpp
	$(CC) $(CFLAGS) $(COPTFLAGS) -c src/asteroid.cpp

bullets.o: src/bullets.cpp
	$(CC) $(CFLAGS) $(COPTFLAGS) -c src/bullets.cpp

ship.o: src/ship.cpp
	$(CC) $(CFLAGS) $(COPTFLAGS) -c src/ship.cpp

transformer.o: src/transformer.cpp $(HEADERS)
	$(CC) $(CFLAGS) $(COPTFLAGS) -c src/transformer.cpp

# Default Targets for Cleaning up the Environment

clean :
	rm bin/*
	rm *.o

pristine :
	rm *.o
	touch *.cpp  

ctags :
	ctags src/*.h *.cpp
