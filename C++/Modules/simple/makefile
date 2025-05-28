BIN=main

CC=g++
CFLAGS=-I. -std=c++2a -fmodules-ts

# Link everything
$(BIN): main.o math.o
	$(CC) $(CFLAGS) main.o math.o -o $(BIN)

# Compile the module interface unit
math.o: math.cxx
	$(CC) $(CFLAGS) -c math.cxx -o math.o

# Compile the main file, importing the module
main.o: main.cpp math.o
	$(CC) $(CFLAGS) -c main.cpp -o main.o

clean:
	rm -f *.o $(BIN)
# ---------------- wildcards -----------------------------------------------------------
# Example:
#  %.o: %.c
# 		gcc -wall -g -c $<
# means: all .o files depend on the corresponding .c file
#        below is the method for how to create them

# -------------------- Automatic variables ----------------------------------------------
# Example:
# all: file1.cpp file2.cpp
#
# $@ : name of the rules target 							(all)
# $^ : list of all dependencies, no duplicates		(file1.cpp file2.cpp)
# $+ : list of all dependencies
# $< : first dependency 									(file1.cpp)

# -------------------- General Comments -------------------------------------------------
# calling make without target parameter creates the first target in the makefile
