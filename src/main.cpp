#include <iostream>
#include <armadillo>


#include "headers/Particle.hpp"
#include "headers/PenningTrap.hpp"

int main(int argc, char const *argv[]){
    /*
    Main cpp file
    */

    double q = 2.;
    double m = 3.;
    double b0 = 9.65e1;
    double v0 = 2.41e6;
    double d = 500;

    arma::vec r = arma::vec(3);
    arma::vec v = arma::vec(3);
    for (arma::uword i = 0; i < 3; i++){
        r[i] = i;
        v[i] = i;
    }

    Particle p = Particle(q, m, r, v);
    PenningTrap trap = PenningTrap(b0,v0,d);
    trap.add_particle(p);

    return 0;
}
