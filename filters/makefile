OBJS = ex2.o
CC = g++
DEBUG = -g
CFLAGS = -Wall -c $(DEBUG)
LFLAGS = -Wall $(DEBUG)

all:prog1 prog2 prog3

prog1:prog1.cpp
	g++ -o myProg1 prog1.cpp `pkg-config opencv --cflags --libs`

prog2: prog2.cpp
	g++ -o myProg2 prog2.cpp `pkg-config opencv --cflags --libs`

prog3: prog3.cpp
	g++ -o myProg3 prog3.cpp `pkg-config opencv --cflags --libs`

clean:
	\rm myProg1 myProg2 myProg3
