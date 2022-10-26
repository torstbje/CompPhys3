#include <iostream>
#include <armadillo>
#include <fstream>
#include <cassert>


#include "headers/Particle.hpp"
#include "headers/PenningTrap.hpp"

using namespace arma;

#define ERR_MISSING_PARAMS 1
#define ERR_INVALID_fVALUE 2
#define ERR_INVALID_NPART  3

/* TODO: external E- and B-fields = 0 (when |r| >d) (done)
   external E-field such that it can have a time dependence (done)
   count how many of the particles are still inside the trap (done)
   is_interact (done)
   filling the PenningTrap with particles with randomly generated initial positions and velocities (done)
 */
void time_evo(PenningTrap &trap, double total_t, int n_steps);
double time_evo_resonance(PenningTrap trap, double total_t, int n_steps);
PenningTrap make_test_trap(int n_part, double q, double m, double b0, double v0, double d, double f, double wv, std::string is_interact, std::string method);
void add_rand_parts(PenningTrap& trap, int n, double q, double m);

int main(int argc, char const *argv[]){
    /*
    Main cpp file
    */

    if (argc < 7){
        std::cout << "\nMissing input parameters! (" << argc - 1 << " parameters was included.) \n"
        "Necessary parameters:\n"
        "-Method ('eul'/'rk4') \n"
        "-Interactions ('0'/'1') \n"
        "-Number of particles (n > 0) \n"
        "-Number of time steps (integer) \n"
        "-Total time (in micro seconds) \n"
        "- value of f (the constant amplitude), one of 0 (not time dependent) 0.1, 0.4, 0.7 \n";
        return ERR_MISSING_PARAMS;
    }

    std::string method = argv[1];
    std::string is_interact = argv[2];
    int n_part = atoi(argv[3]);
    int n_steps = atoi(argv[4]);
    double total_t = std::stod(argv[5]);
    double f = atof(argv[6]);


    if (0 != f && 0.1 != f && 0.4 != f && 0.7 != f) {
        std::cout << "Incorrect value for f, choose from (0, 0.1, 0.4, 0.7)! \n";
        return ERR_INVALID_fVALUE;
    }


    if (n_part < 1){
        std::cout << "System requires at least 1 particle! \n";
        return ERR_INVALID_NPART;
    }


    double q = 1.;
    double m = 40.078;
    double b0 = 96.4852558;
    double v0 = 2.41e6;
    double d = 500;
    arma_rng::set_seed_random();

    // Simulation
    if (n_part < 3) {

        PenningTrap trap = make_test_trap(n_part, q, m, b0, v0, d, f, 0, is_interact, method);

        // Evolve system and write to files
        time_evo(trap, total_t, n_steps);
    }
    else {

        // time-dependent trap
        double wv = 2.3;
        double dwv = 0.02;


        std::ofstream outfile;
        std::string filename = "textfiles/p_frac_" + is_interact +std::to_string(int(total_t)) + "_0." + std::to_string(int(f*10)) + ".txt";
        outfile.open(filename);
        while (wv < 2.5) {
            PenningTrap new_trap = PenningTrap(b0, v0, d, is_interact, method, f, wv);
            add_rand_parts(new_trap, n_part, q, m);
            double part_frac = time_evo_resonance(new_trap, total_t, n_steps);

            outfile << wv << "," << part_frac << std::endl;
            wv += dwv;
        }
        outfile.close();
    }




    return 0;
}

PenningTrap make_test_trap(int n_part, double q, double m, double b0, double v0, double d, double f, double wv, std::string is_interact, std::string method) {

    // Trap
    PenningTrap trap = PenningTrap(b0,v0,d,is_interact,method,f,0);


    // Particle 1
    vec r1 = vec(3);
    vec v1 = vec(3);

    r1[0] = 20;
    r1[2] = 20;
    v1[1] = 25;
    Particle p1 = Particle(q, m, r1, v1);
    trap.add_particle(p1);


    // Particle 2
    if (n_part > 1){
        vec r2 = vec(3);
        vec v2 = vec(3);

        r2[0] = 25;
        r2[1] = 25;
        v2[1] = 40;
        v2[2] = 5;

        Particle p2 = Particle(q, m, r2, v2);
        trap.add_particle(p2);
    }
    return trap;
}

void add_rand_parts(PenningTrap& trap, int n, double q, double m) {

    /*  adds n particles inside the trap
     input:
     trap: trap in which the particles should be added
     n: number of particles*/
    for (int i=0;i<n;i++) {
        vec r = vec(3).randn() * 0.1 * trap.dim;  // random initial position
        vec v = vec(3).randn() * 0.1 * trap.dim;  // random initial velocity
        Particle p = Particle(q, m, r, v);
        trap.add_particle(p);
    }
}

double time_evo_resonance(PenningTrap trap, double total_t, int n_steps) {
    /* Evolves the system for a time dependent electric potential
     and saves them to a text file
     inputs:
     trap: the penning trap
     total_t: total run time
     n_steps: number of steps run
     return: fraction of particles still left in the trap after total_t*/

    double dt = total_t/n_steps;
    int n_part = int(trap.particles.size());
    double curr_t = 0;

    for (int i=1; i < n_steps; i++) {

        trap.evolve(dt, curr_t);
        curr_t += dt;
    }

    return trap.count_particles()/double(n_part);
}


// can be moved elsewhere
void time_evo(PenningTrap& trap, double total_t, int n_steps) {
    /* evolves the system for the specified time,
     save the given particle's trajectory
     inputs:
     trap: PenningTrap object
     total_t: total time run
     n_steps: number of steps
     */

    double dt = total_t/n_steps;
    double curr_t = 0;
    int n_part = int(trap.particles.size());

    std::vector<std::ofstream> outfiles;

    // Make outfiles and write initial values
    for (int j=0; j<n_part; j++) {
        outfiles.emplace_back(std::ofstream{ trap.file_string + std::to_string(n_steps) + '_'+ std::to_string(j) + ".txt" });
        outfiles[j] << curr_t << trap.particles[j].get_string() << std::endl;
    }


    // Update trap and write data to file
    for (int i=1; i < n_steps;i++) {

        trap.evolve(dt, curr_t);
        curr_t += dt;
        for (int j=0; j<n_part; j++) {
            outfiles[j] << curr_t << trap.particles[j].get_string() << std::endl;
        }

    }

    // close files
    for (int j=0; j<n_part;j++) {
        outfiles[j].close();
    }

}
