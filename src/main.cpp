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


    // particle 1
    vec r1 = vec(3);
    vec v1 = vec(3);

    r1[0] = 20;
    r1[2] = 20;
    v1[1] = 25;


    // particle 2
    vec r2 = vec(3);
    vec v2 = vec(3);

    r2[0] = 25;
    r2[1] = 25;
    v2[1] = 40;
    v2[2] = 5;


    Particle p1 = Particle(q, m, r1, v1);
    Particle p2 = Particle(q, m, r2, v2);
    trap.add_particle(p1);
    trap.add_particle(p2);


    vec field = trap.force_particle(0,1);

//    for (int i = 0; i < 3; i++){
//        cout << r[i] << " , " << field[i] << endl;
//    }
    
    // test time evolution
    double dt = 0.01;
    for (int i=0; i<100 ;i++) {
        trap.evolve_RK4(dt);
        cout << trap.particles[0].pos << endl;
    }
     
    // seems okay, now compare to rk4

    return 0;
}
