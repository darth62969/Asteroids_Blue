# Makefile to build "Asteroids: RETURN OF METEOR"
##
# By: 
# Jonathan Oakes
# Braeden Brettin
# Ted Dorfeuille 
# Chris Le
# Emily Herron
#
# Date Last Modified: 12/17/18
#
# License: IDGAF (I don't give a fork) do what ever with this specific file, if it helps you build a better
# makefile then so be it. that's good news for us.

# clipper.o detectcollision.o FileHandler.o render.o -O3 

CC = g++
CFLAGS = -v -std=c++11
COPTFLAGS = -O3
LIBFLAGS = -lglut -lGLU -lGL -lm
HEADERS = src/headers.h src/structs.h src/globals.h src/prototypes.h
OBJ = transformer.o render.o mode.o object.o bullet.o ship.o
#OBJ2 =  enterprise.o normal.o asteroid.o   render.o transformer.o
#OBJ3 = mode.o object.o enterprise.o endless.o asteroid.o ship.o bullet.o render.o transformer.o
SHARED = -shared -fPIC
LINKS = -ldl


debug ?= n
logging ?= n
multit ?=n
shiptest ?=n
windows ?=n

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
ifeq ($(windows), y)
	CC = x86_64-w64-mingw32-g++
	CFLAGS += -I/mnt/d/CSC315/asteroids_blue/lib/freeglut/include/ -DWINDOWS
	LIBFLAGS = -L/mnt/d/CSC315/asteroids_blue/lib/freeglut/lib/x64/ -Wl,--subsystem,windows -lfreeglut -lopengl32 -lglu32 
endif

# Independent Targets - first is executable, second is object
All : AsteroidsCore.so

AsteroidsCore.so : $(OBJ) $(HEADERS)
	$(CC) -o bin/AsteroidsCore.so $(OBJ) $(CFLAGS) $(LIBFLAGS) $(SHARED)

asteroid.o: src/asteroid.cpp
	$(CC) $(CFLAGS) $(COPTFLAGS) -c src/asteroid.cpp $(SHARED)

bullet.o: src/bullet.cpp
	$(CC) $(CFLAGS) $(COPTFLAGS) -c src/bullet.cpp $(SHARED)

ship.o: src/ship.cpp
	$(CC) $(CFLAGS) $(COPTFLAGS) -c src/ship.cpp $(SHARED)

transformer.o: src/transformer.cpp $(HEADERS) 
	$(CC) $(CFLAGS) $(COPTFLAGS) -c src/transformer.cpp $(SHARED)

clipper.o: src/clipper.cpp $(HEADERS)
	$(CC) $(CFLAGS) $(COPTFLAGS) -c src/clipper.cpp

mode.o : src/mode.cpp
	$(CC) $(CFLAGS) $(COPTFLAGS) -c src/mode.cpp $(SHARED)

render.o : src/render.cpp
	$(CC) $(CFLAGS) $(COPTFLAGS) -c src/render.cpp $(SHARED)

object.o : src/object.cpp
	$(CC) $(CFLAGS) $(COPTFLAGS) -c src/object.cpp $(SHARED)



# Default Targets for Cleaning up the Environment

clean :
	rm *.o
	rm bin/Asteroids*

pristine :
	rm *.o
	touch src/*.cpp  

ctags :
	ctags src/*.h src/*.cpp
