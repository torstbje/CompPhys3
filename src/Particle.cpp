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

std::string Particle::get_string(){
    /*
    Returns position and velocity of the particle as a string separated by commas.
    First symbol also a comma. I.e. ",x,y,z,v_x,v_y,v_z"
    */
    std::string pos_string = "";
    std::string vel_string = "";
    for (int i = 0; i < 3; i++) {
        pos_string += "," + std::to_string(pos[i]);
        vel_string += "," + std::to_string(vel[i]);
    }

    return pos_string + vel_string;
}
