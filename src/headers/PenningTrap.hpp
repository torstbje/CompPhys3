#ifndef PENNINGTRAP_HPP
#define PENNINGTRAP_HPP

class PenningTrap{
    /*
    PenningTrap object for storing charged particles
    */

public:

    double mag_field_strength, potential;
    double dim;
    std::vector<Particle> particles;
    std::string ode_type;
    bool is_interact;
    typedef arma::vec (PenningTrap::*force_pointer)(int i);
    typedef void (PenningTrap::*evolve_pointer)(double dt);
    force_pointer force_func;
    evolve_pointer evolve_func;

    // Constructor
  PenningTrap(double B0_in, double V0_in, double d_in, bool interact, std::string method);

  // Add a particle to the trap
  void add_particle(Particle p_in);

  // External electric field at point r=(x,y,z)
  arma::vec external_E_field(arma::vec r);

  // External magnetic field at point r=(x,y,z)
  arma::vec external_B_field(arma::vec r);

  // Force on particle_i from particle_j
  arma::vec force_particle(int i, int j);

  // The total force on particle_i from the external fields
  arma::vec total_force_external(int i);

  // The total force on particle_i from the other particles
  arma::vec total_force_particles(int i);

  // Only used when interaction is included
  arma::vec combine_force(int i);

  // The total force on particle_i from both external fields and other particles
  arma::vec total_force(int i);

  // Pure virtual method for evolving the system one time step (dt)
  void evolve(double dt);
  void evolve_Euler(double dt);
  void evolve_RK4(double dt);

};

#endif
