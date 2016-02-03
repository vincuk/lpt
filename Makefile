# Makefile >> mini shell

CXX=g++
CXXFLAGS=-g -Wall #-std=c++11 -pedantic
BIN=runme

SRC=main.cpp
OBJ=main.o

all: $(OBJ)
	$(CXX) -o $(BIN) $^
