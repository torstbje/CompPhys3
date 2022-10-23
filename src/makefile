all: compile execute

compile:
	g++ -std=c++11 -o main.out main.cpp Particle.cpp BaseTrap.cpp PenningTrapRK4.cpp PenningTrapEuler.cpp -larmadillo -llapack -lblas

execute:
	./main.out
