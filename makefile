all: main.cpp
	g++ -w main.cpp first.cpp terrain.cpp obj1.cpp libtarga.cpp glm.cpp -lGL -lGLU -lglut -O2 -Og -Ofast -o game
