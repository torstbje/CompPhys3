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
