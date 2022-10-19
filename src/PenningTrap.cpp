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
