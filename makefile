all: main.cpp first.cpp terrain.cpp obj1.cpp libtarga.cpp glm.cpp vec3f.cpp
	g++ -w main.cpp first.cpp terrain.cpp obj1.cpp libtarga.cpp glm.cpp vec3f.cpp -lGL -lGLU -lglut -o game -std=c++11 -O2 -Os -Ofast
