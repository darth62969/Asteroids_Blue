# Makefile to build "Asteroids: RETURN OF METEOR"
#
# Origingally for use in Introgl Example 
#
# By:
#
# Andrew J. Pounds, Ph.D.
# Departments of Chemistry and Computer Science
# Mercer University
# Fall 2016 
#
# Modified for use in: "Asteroids: RETURN OF METEOR" 
# Modified by: Blue Squad
# For the class: Introduction to Computer Graphics (CSC315)
# At: Mercer Univercity
#
# Blue Squad is:
# Jonathan Oakes
# Braeden Brettin
# Ted Dorfeuille 
# Chris Le
# Emily Herron
#



CC = g++ 
CFLAGS = 
COPTFLAGS = -O3 
LIBFLAGS = -lglut -lGLU -lGL
HEADERS = src/headers.h src/structs.h src/globals.h src/prototypes.h
OBJS = main.o asteroid.o ship.o bullets.o transformer.o clipper.o

logging ?= y
debug ?= n
ifeq ($(debug), y)
	CFLAGS += -g -DDEBUG -pg
endif

ifeq ($(logging), y)
	CFLAGS += -DLOGGING
endif

# Independent Targets - first is executable, second is object

Asteroids : $(OBJS) $(HEADERS)
	$(CC) -o bin/Asteroids $(OBJS) $(CFLAGS) $(LIBFLAGS)

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

clipper.o: src/clipper.cpp $(HEADERS)
	$(CC) $(CFLAGS) $(COPTFLAGS) -c src/clipper.cpp

# Default Targets for Cleaning up the Environment

clean :
	rm bin/*
	rm *.o

pristine :
	rm *.o
	touch *.cpp  

ctags :
	ctags src/*.h src/*.cpp
