#include <iostream>
#include <armadillo>
#include <fstream>


#include "headers/Particle.hpp"
#include "headers/PenningTrap.hpp"

using namespace arma;


void time_evo(PenningTrap &trap, double total_t, int n_steps);

int main(int argc, char const *argv[]){
    /*
    Main cpp file
    */

    if (argc < 6){
        std::cout << "\nMissing input parameters! (" << argc - 1 << " parameters was included.) \n"
        "Necessary parameters:\n"
        "-Method ('eul'/'rk4') \n"
        "-Interactions ('0'/'1') \n"
        "-Number of particles ('1','2') \n"
        "-Total time (in micro seconds) \n"
        "-Number of time steps (integer) \n";
        return 1;
    }

    std::string method = argv[1];
    std::string is_interact = argv[2];
    int n_part = atoi(argv[3]);
    double total_t = std::stod(argv[4]);
    int n = atoi(argv[5]);


    if (n_part != 1 && n_part != 2){
        std::cout << "Wrong number of particles! Use 1 or 2";
        return 1;
    }

    double q = 1.;
    double m = 1.;
    double b0 = 96.4852558;
    double v0 = 2.41e6;
    double d = 500;


    // Trap
    PenningTrap trap = PenningTrap(b0,v0,d,is_interact,method);


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




    // Evolve system and write to files
    time_evo(trap, total_t, n);

    return 0;
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
    int n_part = trap.particles.size();
    std::vector<std::ofstream> outfiles;

    // Make outfiles and write initial values
    for (int j=0; j<n_part; j++) {
        outfiles.emplace_back(std::ofstream{ trap.file_string + std::to_string(j) + ".txt" });
        outfiles[j] << 0 << trap.particles[j].get_string() << std::endl;
    }

    // Update trap and write data to file
    for (int i=1; i < n_steps;i++) {

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
