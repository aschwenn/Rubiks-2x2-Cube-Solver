# makefile

all: solver

solver: solver.cpp Row.h Row.cpp Side.h Side.cpp Cube.h Cube.cpp
	g++ -g -o solver solver.cpp Row.h Row.cpp Side.h Side.cpp Cube.h Cube.cpp

clean:
	rm -f solver
