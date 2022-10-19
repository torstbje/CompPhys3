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

    arma::vec r = arma::vec(3);
    arma::vec v = arma::vec(3);
    for (arma::uword i = 0; i < 3; i++){
        r[i] = i;
        v[i] = i;
    }

    Particle p = Particle(q, m, r, v);
    

    return 0;
}
