#ifndef PENNINGTRAP_HPP
#define PENNINGTRAP_HPP

class BaseTrap{
    /*
    Abstract base class for the Penning Trap subclasses.
    Contains virtual method for evolving the system.
    */

public:

    double mag_field_strength, potential;
    double dim;
    std::vector<Particle> particles;
    std::string ode_type;

    // Constructor
  BaseTrap(double B0_in, double V0_in, double d_in);

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

  // The total force on particle_i from both external fields and other particles
  arma::vec total_force(int i, int is_interact);

  // Pure virtual method for evolving the system one time step (dt)
  virtual void evolve(double dt, int is_interact) = 0;

};

// Child classes

class PenningTrapEuler : public BaseTrap{
    /*
    Penning trap child class with Euler as method for evolving system.
    */

public:
    PenningTrapEuler(double B0_in, double V0_in, double d_in) : BaseTrap(B0_in,V0_in,d_in){ode_type = "eul";};
    void evolve(double dt, int is_interact);
};

class PenningTrapRK4 : public BaseTrap{
    /*
    Penning trap child class with RK4 as method for evolving system.
    */

public:
    PenningTrapRK4(double B0_in, double V0_in, double d_in) : BaseTrap(B0_in,V0_in,d_in){ode_type = "rk4";};
    void evolve(double dt, int is_interact);
};

#endif
