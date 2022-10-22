#include <iostream>
#include <armadillo>
#include <fstream>


#include "headers/Particle.hpp"
#include "headers/PenningTrap.hpp"

using namespace arma;

void time_evo(PenningTrap trap, double dt, double total_t, std::string filename, int part_int, int is_euler=0);

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
    
    // test time evolution for one particle for 50μs
   
    std::string euler_file = "textfiles/z_euler.txt";
    std::string rk4_file = "textfiles/z_rk4.txt";
    
    double total_t = 50;
    double dt = 0.01;
    
    time_evo(trap, dt, total_t, euler_file, 0, 1);
    time_evo(trap, dt, total_t, rk4_file, 0, 0);
    

    return 0;
}


void time_evo(PenningTrap trap, double dt, double total_t, std::string filename, int part_int, int is_euler) {
    /* evolves the system for the specified time without changing values in trap
     inputs:
     dt: time step size
     total_t: total time run
     filename: where to save the positions
     part_int: which particle's z position to save
     */
    
    std::ofstream outfile;
    outfile.open(filename);
    for (int i=0; i<total_t/dt ;i++) {
        // use rk4
        if (is_euler)
            trap.evolve_forward_Euler(dt);
        else
            trap.evolve_RK4(dt);
        
        outfile << i*dt << "," << trap.particles[part_int].pos[2] << std::endl;

    }
}
