#ifndef PENNINGTRAP_HPP
#define PENNINGTRAP_HPP

class PenningTrap{
    /*
    PenningTrap object for storing charged particles
    */

private:
    typedef arma::vec (PenningTrap::*force_pointer)(int i, double t);
    typedef void (PenningTrap::*evolve_pointer)(double dt, double t);
    force_pointer force_func;
    evolve_pointer evolve_func;

public:

    double mag_field_strength, potential;
    double dim;
    std::vector<Particle> particles;
    std::string file_string;
    int f;
    double wv;


    // Constructor
  PenningTrap();

  PenningTrap(double B0_in, double V0_in, double d_in, std::string is_interact, std::string method, double amplitude, double w_v);

  // Add a particle to the trap
  void add_particle(Particle p_in);

  // External electric field at point r=(x,y,z)
  arma::vec external_E_field(arma::vec r, double t);

  // External magnetic field at point r=(x,y,z)
  arma::vec external_B_field(arma::vec r);

  // Force on particle_i from particle_j
  arma::vec force_particle(int i, int j);

  // The total force on particle_i from the external fields
  arma::vec total_force_external(int i, double t);

  // The total force on particle_i from the other particles
  arma::vec total_force_particles(int i);

  // Only used when interaction is included
  arma::vec combine_force(int i, double t);

  // The total force on particle_i from both external fields and other particles
  arma::vec total_force(int i, double t);

  // Method for evolving the system one time step (dt)
  void evolve(double dt, double t);

  // This method is used for evolve if method = "eul"
  void evolve_Euler(double dt, double t);

  // This method is used for evolve otherwise (method != "eul")
  void evolve_RK4(double dt, double t);
  
  // This method counts and returns the number of particles that are inside the trap
  int count_particles();
};

#endif
