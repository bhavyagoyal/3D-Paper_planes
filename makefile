all: main.cpp
	g++ main.cpp -lGL -lGLU -lglut -O2 -Og -Ofast -o game
