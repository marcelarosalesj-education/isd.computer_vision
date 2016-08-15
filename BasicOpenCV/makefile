CC = g++
DEBUG = -g
CFLAGS = -Wall -c $(DEBUG)
LFLAGS = -Wall $(DEBUG)

all: main

main: main.cpp
	g++ -o main main.cpp `pkg-config opencv --cflags --libs`