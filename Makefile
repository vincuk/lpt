# Makefile >> mini shell

CXX=g++
CXXFLAGS=-g -std=c++11 #-Wall -pedantic
BIN=runme

SRC=main.cpp
OBJ=main.o

all: $(OBJ)
	$(CXX) -o $(BIN) $^
