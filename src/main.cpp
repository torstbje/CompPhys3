#include <iostream>
#include <armadillo>


#include "headers/Particle.hpp"
#include "headers/PenningTrap.hpp"

using namespace arma;

int main(int argc, char const *argv[]){
    /*
    Main cpp file
    */

    double q = 1.;
    double m = 1.;
    double b0 = 9.65e1;
    double v0 = 2.41e6;
    double d = 500;

    PenningTrap trap = PenningTrap(b0,v0,d);
    vec r = vec(3).randn() * 0.1 * trap.dim;  // random initial position
    vec v = vec(3).randn() * 0.1 * trap.dim;  // random initial velocity

    Particle p = Particle(q, m, r, v);
    trap.add_particle(p);


    return 0;
}
