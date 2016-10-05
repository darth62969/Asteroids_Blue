# Makefile to build introgl example 
#
# Andrew J. Pounds, Ph.D.
# Departments of Chemistry and Computer Science
# Mercer University
# Fall 2016 
#

CC = g++ 
CFLAGS = 
COPTFLAGS = -O3 
LIBFLAGS = -lglut -lGLU -lGL

# Independent Targets - first is executable, second is object

main : main.o  
	$(CC) main.o -o bin/main $(LIBFLAGS) 	

main.o : src/main.cpp
	$(CC) $(CFLAGS) $(COPTFLAGS) -c src/main.cpp


# Default Targets for Cleaning up the Environment

clean :
	rm *.o

pristine :
	rm *.o
	touch *.cpp  

ctags :
	ctags *.cpp

