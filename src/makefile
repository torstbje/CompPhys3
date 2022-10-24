all: compile execute

compile:
	g++ -std=c++17 -o main.out main.cpp Particle.cpp PenningTrap.cpp -larmadillo -llapack -lblas

execute: euler rk4 euler_non rk4_non

euler:
	./main.out eul 1

rk4:
	./main.out rk4 1

euler_non:
	./main.out eul 0

rk4_non:
	./main.out rk4 0
