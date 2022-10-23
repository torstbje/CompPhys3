#include <iostream>
#include <armadillo>
#include <fstream>


#include "headers/Particle.hpp"
#include "headers/PenningTrap.hpp"

using namespace arma;


void time_evo(PenningTrap trap, double dt, double total_t, int part_int, int is_interact, int is_euler=0);

int main(int argc, char const *argv[]){
    /*
    Main cpp file
    */

    double q = 1.;
    double m = 1.;
    double b0 = 96.4852558;
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
   
    std::string euler_file = "textfiles/pos_euler.txt";
    std::string rk4_file = "textfiles/pos_rk4.txt";
    
    double total_t = 50;
//    double n_steps = 4000;
//    double dt = total_t/n_steps;
    double dt = 0.001;
    
    std::string filenames_int, filenames_non;
    // euler
//    time_evo(trap, dt, total_t, 2, 1, 1);
    
    // rk4
    
    // interaction
    time_evo(trap, dt, total_t, 2, 1, 0);
    
    // no interaction
    time_evo(trap, dt, total_t, 2, 0, 0);
    
    return 0;
}


// can be moved elsewhere
void time_evo(PenningTrap trap, double dt, double total_t, int n_part, int is_interact, int is_euler) {
    /* evolves the system for the specified time without changing values in trap,
     save the given particle's trajectory
     inputs:
     dt: time step size
     total_t: total time run
     filename: where to save the positions
     part_int: which particle's z position to save
     
     return:
     vector of filenames
     */
    
    std::ofstream outfile;
    std::string filename = "textfiles/pos_";
    std::string filenames;

    
    if (is_euler)
        filename += "eul_";
    else
        filename += "rk4_";
        
    if (is_interact)
        filename += "int_";
    else
        filename += "non_";

    for (int i=0; i<n_part;i++) {
        outfile.open(filename + std::to_string(i) + ".txt");
        outfile.close();
    }
    
    
    for (int i=0; i<total_t/dt; i++) {
        
        // use rk4
        if (is_interact) {
            if (is_euler) {
                trap.evolve_forward_Euler(dt, is_interact);
                
            }
            else {
                trap.evolve_RK4(dt, is_interact);
            }
        }
        
        else {
            if (is_euler) {
                trap.evolve_forward_Euler(dt, is_interact);
                
            }
            else {
                trap.evolve_RK4(dt, is_interact);
            }
        }
        
        
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

