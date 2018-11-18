CC = g++
DEBUG = -g
CFLAGS = -Wall -c $(DEBUG)
LFLAGS = -Wall $(DEBUG)

mean5x5: mean5x5.cpp
	g++ -std=c++17 -o mean5x5.o mean5x5.cpp `pkg-config opencv4 --cflags --libs`

colormap: colormap.cpp
	g++ -std=c++17 -o colormap.o colormap.cpp `pkg-config opencv4 --cflags --libs` -lstdc++fs 
