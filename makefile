all: main.cpp
	g++ main.cpp first.cpp terrain.cpp -lGL -lGLU -lglut -O2 -Og -Ofast -o game
