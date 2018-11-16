CC = g++
DEBUG = -g
CFLAGS = -Wall -c $(DEBUG)
LFLAGS = -Wall $(DEBUG)

all: main

main: main.cpp
	g++ -std=c++17 -o main.o main.cpp -I/usr/local/include/opencv4 -lstdc++fs -lopencv_highgui -lopencv_imgproc -lopencv_imgcodecs -lopencv_core
