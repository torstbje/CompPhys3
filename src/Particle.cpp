#include <armadillo>

#include "headers/Particle.hpp"

Particle::Particle(double q, double m, arma::vec r, arma::vec v){
    /*
    Initializer for Particle class
    */
    charge = q;
    mass = m;
    pos = r;
    vel = v;
}
