all: compile execute

compile:
	g++ -std=c++17 -o main.out main.cpp Particle.cpp PenningTrap.cpp -larmadillo -llapack -lblas

execute: euler rk4 euler_non rk4_non

euler:
	./main.out eul int 2 50 50000

rk4:
	./main.out rk4 int 2 50 50000

euler_non:
	./main.out eul non 2 50 50000

rk4_non:
	./main.out rk4 non 2 50 50000
