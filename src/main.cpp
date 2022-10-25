#include <iostream>
#include <armadillo>
#include <fstream>


#include "headers/Particle.hpp"
#include "headers/PenningTrap.hpp"

using namespace arma;


void time_evo(PenningTrap &trap, double dt, double total_t);

int main(int argc, char const *argv[]){
    /*
    Main cpp file
    */

    if (argc < 3){
        std::cout << "Include parameters for method and interactions you doofus";
        return 1;
    }

    std::string method = argv[1];
    std::string is_interact = argv[2];

    double q = 1.;
    double m = 1.;
    double b0 = 96.4852558;
    double v0 = 2.41e6;
    double d = 500;


    // particle 1
    vec r1 = vec(3);
    vec v1 = vec(3);

    r1[0] = 20;
    r1[2] = 20;
    v1[1] = 25;
    Particle p1 = Particle(q, m, r1, v1);


    // particle 2
    vec r2 = vec(3);
    vec v2 = vec(3);

    r2[0] = 25;
    r2[1] = 25;
    v2[1] = 40;
    v2[2] = 5;

    Particle p2 = Particle(q, m, r2, v2);


    // test time evolution for one particle for time: 50μs

    double total_t = 50;
    double dt = 0.001;

    PenningTrap trap = PenningTrap(b0,v0,d,is_interact,method);
    trap.add_particle(p1);
    trap.add_particle(p2);
    time_evo(trap, dt, total_t);

    return 0;
}


// can be moved elsewhere
void time_evo(PenningTrap& trap, double dt, double total_t) {
    /* evolves the system for the specified time,
     save the given particle's trajectory
     inputs:
     trap: PenningTrap object
     dt: time step size
     total_t: total time run
     */

    int n_part = trap.particles.size();
    std::vector<std::ofstream> outfiles;

    // Make outfiles and write initial values
    for (int j=0; j<n_part; j++) {
        outfiles.emplace_back(std::ofstream{ trap.file_string + std::to_string(j) + ".txt" });
        outfiles[j] << 0 << trap.particles[j].get_string() << std::endl;
    }

    // Update trap and write data to file
    for (int i=1; i < total_t/dt;i++) {

        trap.evolve(dt);

        for (int j=0; j<n_part; j++) {
            outfiles[j] << i*dt << trap.particles[j].get_string() << std::endl;
        }

    }

    // close files
    for (int j=0; j<n_part;j++) {
        outfiles[j].close();
    }

}
