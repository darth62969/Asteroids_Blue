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
# At: Mercer University
#
# Blue Squad is:
# Jonathan Oakes
# Braeden Brettin
# Ted Dorfeuille 
# Chris Le
# Emily Herron
#

CC = g++
CFLAGS = -v -std=c++11
COPTFLAGS = -O3 
LIBFLAGS = -lglut -lGLU -lGL -lm 
HEADERS = src/headers.h src/structs.h src/globals.h src/prototypes.h
OBJS = main.o asteroid.o ship.o bullet.o transformer.o clipper.o detectcollision.o FileHandler.o

debug ?= n
logging ?= n
multit ?=n
shiptest ?=n

ifeq ($(shiptest), y)
	CFLAGS += -DSHIPTEST
endif

ifeq ($(debug), y)
	CFLAGS += -g -DDEBUG -pg
endif

ifeq ($(logging), y)
	CFLAGS += -DLOGGING
endif
ifeq ($(multit), y)
	CFLAGS += -DMULTIT
endif

# Independent Targets - first is executable, second is object

Asteroids : $(OBJS) $(HEADERS)
	$(CC) -o bin/Asteroids $(OBJS) $(CFLAGS) $(LIBFLAGS)

#I wish we could have figured out how to make it so that these files went into /bin and not the main folder.
main.o : src/main.cpp $(HEADERS)
	$(CC) $(CFLAGS) $(COPTFLAGS) -c src/main.cpp

asteroid.o: src/asteroid.cpp
	$(CC) $(CFLAGS) $(COPTFLAGS) -c src/asteroid.cpp

bullet.o: src/bullet.cpp
	$(CC) $(CFLAGS) $(COPTFLAGS) -c src/bullet.cpp

ship.o: src/ship.cpp
	$(CC) $(CFLAGS) $(COPTFLAGS) -c src/ship.cpp

transformer.o: src/transformer.cpp $(HEADERS)
	$(CC) $(CFLAGS) $(COPTFLAGS) -c src/transformer.cpp

clipper.o: src/clipper.cpp $(HEADERS)
	$(CC) $(CFLAGS) $(COPTFLAGS) -c src/clipper.cpp

detectcollision.o : src/detectcollision.cpp
	$(CC) $(CFLAGS) $(COPTFLAGS) -c src/detectcollision.cpp

FileHandler.o : src/FileHandler.cpp
	$(CC) $(CFLAGS) $(COPTFLAGS) -c src/FileHandler.cpp

# Default Targets for Cleaning up the Environment

clean :
	rm *.o
	rm bin/*

pristine :
	rm *.o
	touch src/*.cpp  

ctags :
	ctags src/*.h src/*.cpp
