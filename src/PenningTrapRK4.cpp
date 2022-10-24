#include <iostream>
#include <armadillo>

#include "headers/Particle.hpp"
#include "headers/PenningTrap.hpp"


void PenningTrapRK4::evolve(double dt){
    /*
    Evolves the system one timestep dt with the 'RungeKutta4' method
    */

    // make copy of the particles so that the intitial values remains unchanged
    // get the number of particles
    int N = int(particles.size());
    std::vector<Particle> particles_copy;
    for (int i = 0; i < N; i++)
            particles_copy.push_back(particles[i]);

    std::vector<arma::vec> k1r, k2r, k3r, k4r;
    std::vector<arma::vec> k1v, k2v, k3v, k4v;


    // calculates the k's for r and v
    for (int i = 0; i < N; i++){

        // k1
        k1r.push_back(particles_copy[i].vel);
        k1v.push_back(total_force(i)/particles_copy[i].mass);

        // update the copied particles possitions
        particles_copy[i].pos += k1r[i] * dt/2;
        particles_copy[i].vel += k1v[i] * dt/2;

    }

     for (int i = 0; i < N; i++){

        // k2
        k2r.push_back(particles_copy[i].vel);
        k2v.push_back(total_force(i)/particles[i].mass);
        particles_copy[i].pos += k2r[i] * dt/2;
        particles_copy[i].vel += k2v[i] * dt/2;

    }


    for (int i=0;i<N;i++) {

        // k3
        k3r.push_back(particles_copy[i].vel);
        k3v.push_back(total_force(i)/particles[i].mass);
        particles_copy[i].pos += k3r[i] * dt;
        particles_copy[i].vel += k3v[i] * dt;
    }

    for (int i=0;i<N;i++) {

        // k4
        k4r.push_back(particles_copy[i].vel);
        k4v.push_back(total_force(i)/particles[i].mass);
    }

    for (int i = 0; i < N; i++){

        particles[i].pos += (k1r[i] + 2*k2r[i] + 2*k3r[i] + k4r[i]) * dt / 6;
        // update velocity
        particles[i].vel += (k1v[i] + 2*k2v[i] + 2*k3v[i] + k4v[i]) * dt / 6;
    }
}
