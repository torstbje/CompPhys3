all: compile execute

compile:
	g++ -std=c++17 -o main.out main.cpp Particle.cpp PenningTrap.cpp -O2 -larmadillo -llapack -lblas

execute: 1p 2p 1p_err


1p:
	./main.out eul non 1 32000 50 0
	./main.out rk4 non 1 32000 50 0
	python3 plot_1p.py eul 32000 0
	python3 plot_1p.py rk4 32000 0

2p:
	./main.out eul int 2 32000 50 0
	./main.out eul non 2 32000 50 0
	./main.out rk4 int 2 32000 50 0
	./main.out rk4 non 2 32000 50 0
	python3 plot_2p.py eul non 32000
	python3 plot_2p.py eul int 32000
	python3 plot_2p.py rk4 non 32000
	python3 plot_2p.py rk4 int 32000

2p_eul:
	./main.out eul int 2 32000 50 0
	./main.out eul non 2 32000 50 0
	python3 plot_2p.py eul non 32000
	python3 plot_2p.py eul int 32000

2p_rk4:
	./main.out rk4 int 2 32000 500 0
	./main.out rk4 non 2 32000 500 0
	python3 plot_2p.py rk4 non 32000
	python3 plot_2p.py rk4 int 32000


1p_err:
	./main.out rk4 non 1 4000 50 0
	./main.out rk4 non 1 8000 50 0
	./main.out rk4 non 1 16000 50 0
	./main.out rk4 non 1 32000 50 0
	python3 plot_rel_error.py rk4

	./main.out eul non 1 4000 50 0
	./main.out eul non 1 8000 50 0
	./main.out eul non 1 16000 50 0
	./main.out eul non 1 32000 50 0
	python3 plot_rel_error.py eul

test:
#	./main.out eul non 100 4000 500 0.1
	./main.out rk4 non 100 4000 500 0.1
	./main.out rk4 non 100 40000 500 0.4
	./main.out rk4 non 100 40000 500 0.7
	python3 plot_100p.py
