# Makefile >> mini shell

CXX=g++
CXXFLAGS=-g -Wall #-std=c++11 -pedantic
BIN=runme

SRC=posix_main.cpp
OBJ=posix_main.o

all: $(OBJ)
	$(CXX) -o $(BIN) -lpthread $^
