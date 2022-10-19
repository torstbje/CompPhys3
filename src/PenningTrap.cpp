#include <iostream>
#include <armadillo>


#include "headers/Particle.hpp"
#include "headers/PenningTrap.hpp"

PenningTrap::PenningTrap(double b0, double v0, double d){
    /*
    Initializer for Particle class
    */
    mag_field_strength = b0;
    potential = v0;
    dim = d;
}
