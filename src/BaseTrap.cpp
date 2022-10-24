#include <iostream>
#include <armadillo>

#include "headers/Particle.hpp"
#include "headers/PenningTrap.hpp"



BaseTrap::BaseTrap(double b0, double v0, double d, bool interact){
    /*
    Initializer for PenningTrap class
    */
    mag_field_strength = b0;
    potential = v0;
    dim = d;
    is_interact = interact;

    // This block decides which forces are used for the system
    if (is_interact){
        force_func = &BaseTrap::combine_force;
    }
    else {
        force_func = &BaseTrap::total_force_external;
    }

}

void BaseTrap::add_particle(Particle p_in){
    /*
    Adds Particle to the Penning trap
    */
    particles.push_back(p_in);
}

arma::vec BaseTrap::external_E_field(arma::vec r){
    /*
    Evaluates external electric field at given coordinates
    */

    double v0_d2 = 9.65;
    arma::vec e_field = r*v0_d2;
    e_field[2] *= -2;
    return e_field;
}

arma::vec BaseTrap::external_B_field(arma::vec r){
    /*
    Evaluates external magnetic field at given coordinates
    */
    arma::vec b_field(3);
    b_field[2] = mag_field_strength;
    return b_field;
}

arma::vec BaseTrap::force_particle(int i, int j){
    /*
    Evaluates interaction force between particles
    */
    const double k_e = 1.38935333e5;
    arma::vec diff = particles[i].pos - particles[j].pos;
    // distance(3) between ith and jth particle
    arma::vec force = k_e * particles[i].charge * particles[j].charge * diff/(pow(abs(diff),3));
    return force;
}

arma::vec BaseTrap::total_force_external(int i){
    /*
    Evaluates force from external electric and magnetic fields for a given particle
    */
    Particle p = particles[i];
    arma::vec e_field = external_E_field(p.pos);
    arma::vec b_field = external_B_field(p.pos);
    arma::vec ext_force = p.charge*(e_field + arma::cross(p.vel, b_field));
    return ext_force;
}

arma::vec BaseTrap::total_force_particles(int i){
    /*
    Evaluates force on a given particle from interactions with all other particles in the system
    */
    arma::vec int_force(3);
    for (int j = 0; j < particles.size(); j++){
        if (i != j){
            int_force += force_particle(i,j);
        }
    }
    return int_force;
}

arma::vec BaseTrap::combine_force(int i){
    /*
    Evaluates force on a given particle from interactions with all other particles in the system
    */
    return total_force_external(i) + total_force_particles(i);
}

arma::vec BaseTrap::total_force(int i){
    /*
    Evaluates the relevant forces for particle i.
    Method for relevant forces is declared at initialization.
    One of 'combine_force' or 'total_force_external' is used.
    */

    return (this->*force_func)(i);
}
