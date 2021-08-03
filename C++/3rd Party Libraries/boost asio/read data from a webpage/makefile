BIN=main

CC=g++
CFLAGS=-I.

$(BIN): *.cpp
	$(CC) -g -o $@ *.cpp $(CFLAGS) -lpthread -lboost_system

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
