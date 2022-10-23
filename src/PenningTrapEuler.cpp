#include <iostream>
#include <armadillo>

#include "headers/Particle.hpp"
#include "headers/PenningTrap.hpp"


void PenningTrapEuler::evolve(double dt, int is_interact) {
    /*
     Evolves the system one timestep dt with the 'Euler' method
     */

    for (int i = 0; i < particles.size(); i++){
        // update position
        particles[i].pos += particles[i].vel*dt;
        // update velocity
        particles[i].vel += total_force(i, is_interact) / particles[i].mass * dt;
    }
}