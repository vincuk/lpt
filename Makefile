# Makefile >> mini shell

CXX=g++
CXXFLAGS=-g -Wall #-std=c++11 -pedantic
BIN=runme

SRC=sysv_main.cpp
OBJ=sysv_main.o

all: $(OBJ)
	$(CXX) -o $(BIN) $^
