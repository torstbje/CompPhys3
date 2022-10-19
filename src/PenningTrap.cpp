#include <iostream>
#include <armadillo>


#include "headers/Particle.hpp"
#include "headers/PenningTrap.hpp"

PenningTrap::PenningTrap(double b0, double v0, double d){
    /*
    Initializer for PenningTrap class
    */
    mag_field_strength = b0;
    potential = v0;
    dim = d;
}

void PenningTrap::add_particle(Particle p_in){
    /*
    Adds Particle to the Penning trap
    */
    particles.push_back(p_in);
}

arma::vec PenningTrap::external_E_field(arma::vec r){
    /*
    Evaluates external electric field at given coordinates
    */

    arma::vec e_field = r*(potential/(dim*dim));
    e_field[2] *= -2;
    return e_field;
}

arma::vec PenningTrap::external_B_field(arma::vec r){
    /*
    Evaluates external magnetic field at given coordinates
    */
    arma::vec b_field(3);
    b_field[2] = mag_field_strength;
    return b_field;
}

arma::vec PenningTrap::force_particle(int i, int j){
    /*
    Evaluates interaction force between particles
    */
    double k_e = 1.389e5;
    arma::vec diff = particles[i].pos - particles[j].pos;
    arma::vec force = k_e*particles[i].charge*diff/(pow(abs(diff),3));
    return force;
}

arma::vec PenningTrap::total_force_external(int i){
    /*
    Evaluates force from external electric and magnetic fields for a given particle
    */
    Particle p = particles[i];
    arma::vec e_field = external_E_field(p.pos);
    arma::vec b_field = external_B_field(p.pos);
    arma::vec ext_force = p.charge*(e_field + arma::cross(p.vel, b_field));
    return ext_force;
}

arma::vec PenningTrap::total_force_particles(int i){
    /*
    Evaluates force on a given particle from interactions with all other particles in the system
    */
    Particle p = particles[i];
    arma::vec int_force(3);
    for (int j = 0; j < particles.size(); j++){
        if (i != j){
            int_force += force_particle(i,j);
        }
    }
    return int_force;
}

arma::vec PenningTrap::total_force(int i){
    /*
    Evaluates total internal and external forces for a given particle
    */
    return total_force_external(i) + total_force_particles(i);
}


void PenningTrap::evolve_RK4(double dt){
    /*
    Evolves the system on timestep dt with the 'RungeKutta4' method
    */
    for (int i = 0; i < particles.size(); i++){
        return;
    }
}
