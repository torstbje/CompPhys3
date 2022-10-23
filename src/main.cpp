#include <iostream>
#include <armadillo>
#include <fstream>


#include "headers/Particle.hpp"
#include "headers/PenningTrap.hpp"

using namespace arma;


void time_evo(BaseTrap &trap, double dt, double total_t, int part_int, int is_interact);

int main(int argc, char const *argv[]){
    /*
    Main cpp file
    */

    double q = 1.;
    double m = 1.;
    double b0 = 96.4852558;
    double v0 = 2.41e6;
    double d = 500;


    PenningTrapEuler trap1 = PenningTrapEuler(b0,v0,d);
    PenningTrapRK4 trap2 = PenningTrapRK4(b0,v0,d);


    // particle 1
    vec r1 = vec(3);
    vec v1 = vec(3);

    r1[0] = 20;
    r1[2] = 20;
    v1[1] = 25;
    Particle p1 = Particle(q, m, r1, v1);

    trap1.add_particle(p1);
    trap2.add_particle(p1);


    // particle 2
    vec r2 = vec(3);
    vec v2 = vec(3);

    r2[0] = 25;
    r2[1] = 25;
    v2[1] = 40;
    v2[2] = 5;

    Particle p2 = Particle(q, m, r2, v2);
    trap1.add_particle(p2);
    trap2.add_particle(p2);


    // test time evolution for one particle for time: 50μs

    double total_t = 50;
    double dt = 0.001;

    // euler
    time_evo(trap1, dt, total_t, 2, 1);

    // rk4

    // interaction
    time_evo(trap2, dt, total_t, 2, 1);

    // no interaction
    time_evo(trap2, dt, total_t, 2, 0);

    return 0;
}


// can be moved elsewhere
void time_evo(BaseTrap& trap, double dt, double total_t, int n_part, int is_interact) {
    /* evolves the system for the specified time without changing values in trap,
     save the given particle's trajectory
     inputs:
     dt: time step size
     total_t: total time run
     filename: where to save the positions
     part_int: which particle's z position to save

     return:
     nothing / (vector of filenames)
     */


    //std::string odetype = trap.ode_type();

    std::ofstream outfile;
    std::string filename = "textfiles/pos_" + trap.ode_type + "_";


    if (is_interact)
        filename += "int_";
    else
        filename += "non_";


    for (int i=0; i<n_part;i++) {
        outfile.open(filename + std::to_string(i) + ".txt");
        outfile.close();
    }


    for (int i=0; i<total_t/dt; i++) {

        trap.evolve(dt,is_interact);


        for (int j=0; j<n_part; j++) {

            std::string new_filename = filename + std::to_string(j) + ".txt";
            outfile.open(new_filename, ios::out | ios::app);

            outfile << i*dt << "," << trap.particles[j].pos[0] << "," <<
            trap.particles[j].pos[1] << "," << trap.particles[j].pos[2]
            << std::endl;

            outfile.close();
        }

    }


}
