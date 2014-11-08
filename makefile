all: main.cpp first.cpp terrain.cpp obj1.cpp libtarga.cpp glm.cpp Vector3D.cpp
	g++ -w main.cpp first.cpp terrain.cpp obj1.cpp libtarga.cpp glm.cpp Vector3D.cpp -lGL -lGLU -lglut -o game
