# Makefile to build introgl example 
#
# Andrew J. Pounds, Ph.D.
# Departments of Chemistry and Computer Science
# Mercer University
# Fall 2016 
#
# Modified for use in: The Blue Team's Asteroids 
# Modified by: Jonathan Oakes
#

CC = g++ 
CFLAGS = 
COPTFLAGS = -O3 
LIBFLAGS = -lglut -lGLU -lGL

# Independent Targets - first is executable, second is object

asteroids : main.o  
	$(CC) asteroids.o -o bin/asteroids $(LIBFLAGS) 	

asteroids.o : src/asteroids.cpp
	$(CC) $(CFLAGS) $(COPTFLAGS) -c src/asteroids.cpp

asteroid.o :
	$(CC) $(CFLAGS) $(COPTFLAGS) -c src/asteroid.cpp


# Default Targets for Cleaning up the Environment

clean :
	rm *.o

pristine :
	rm *.o
	touch *.cpp  

ctags :
	ctags *.cpp

