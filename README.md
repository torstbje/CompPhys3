# Computational Physics Project 3: Simulations of Penning trap

## DESCRIPTION
- The project simulates a physical system for storing charged particles in electromagnetic fields.
- It uses numerical methods to update position and velocity of particles.
- The simulation is written in object oriented C++ code.
- Plotting and error measurements are written in python3.
- A makefile is used to compile the code, and perform predetermined executions.


## PRODUCE RESULTS
- The code is run from 'src' folder
- make compile: Compiles the c++ program.
- make execute: Makes all relevant results.
- make all: Performs both 'compile' and 'execute'.
- make 1p: Collects the results for one particle simulations. (Position(z) vs time).
- make 2p: Collects the results for two particle simulations. (2D plane, 3D space, phase space).


## GENERAL PROCESS FOR HOW THE CODE RUNS
- src/: Premade makefile commands are run to start program.
- makefile: comiles c++ program.
- makefile: executes c++ code with arguments for which type of simulation to run (i.e. time,steps).
- c++: (Object) PenningTrap is made and filled with instances of (Object) Particle.
- c++: Simulation is performed, with description of system written to txt files at every time step.
- c++: txt files are saved to 'textfiles' folder.
- makefile: executes python functions with specific commands to use the files from the simulation.
- python: txt files are read and relevant data is collected.
- python: data is used for producing figures, or for comparing with analytical solutions.
- python: Figures are saved to 'plots' folder.

## CODE STRUCTURE
- The code contains two classes Particle and PenningTrap.
- The particle class contains a few values and a method returning a string description.
- PenningTrap contains various methods for calculating forces on the particles.
- PenningTrap also contains methods for evolving system with both Forward Euler as well as RK4.
- PenningTrap is initialized, two class function pointers are assigned.
- One pointer is assigned to Euler or RK4.
- The other pointer is assigned to use only external fields, or external + internal.

- Most of the python functions are put in separate files to make it easier to call from makefile.


## CONVENTIONS:
- snake_case (lower case letters separated by an underscore) is used for most variable- and function-names.
- PascalCase (first letter of every word is capitalized, including the very first word) is used for class names.
