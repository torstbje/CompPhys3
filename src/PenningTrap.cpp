#include <iostream>
#include <armadillo>


#include "headers/Particle.hpp"
#include "headers/PenningTrap.hpp"

PenningTrap::PenningTrap(double b0, double v0, double d){
    /*
    Initializer for PenningTrap class
    */
    mag_field_strength = b0;
    potential = v0;
    dim = d;
   
}

void PenningTrap::add_particle(Particle p_in){
    /*
    Adds Particle to the Penning trap
    */
    particles.push_back(p_in);
}

arma::vec PenningTrap::external_E_field(arma::vec r){
    /*
    Evaluates external electric field at given coordinates
    */
    
    double v0_d2 = 9.65;
    arma::vec e_field = r*v0_d2;
    e_field[2] *= -2;
    return e_field;
}

arma::vec PenningTrap::external_B_field(arma::vec r){
    /*
    Evaluates external magnetic field at given coordinates
    */
    arma::vec b_field(3);
    b_field[2] = mag_field_strength;
    return b_field;
}

arma::vec PenningTrap::force_particle(int i, int j){
    /*
    Evaluates interaction force between particles
    */
    const double k_e = 1.38935333e5;
    arma::vec diff = particles[i].pos - particles[j].pos;
    // distance(3) between ith and jth particle
    arma::vec force = k_e * particles[i].charge * particles[j].charge * diff/(pow(abs(diff),3));
    return force;
}

arma::vec PenningTrap::total_force_external(int i){
    /*
    Evaluates force from external electric and magnetic fields for a given particle
    */
    Particle p = particles[i];
    arma::vec e_field = external_E_field(p.pos);
    arma::vec b_field = external_B_field(p.pos);
    arma::vec ext_force = p.charge*(e_field + arma::cross(p.vel, b_field));
    return ext_force;
}

arma::vec PenningTrap::total_force_particles(int i){
    /*
    Evaluates force on a given particle from interactions with all other particles in the system
    */
    arma::vec int_force(3);
    for (int j = 0; j < particles.size(); j++){
        if (i != j){
            int_force += force_particle(i,j);
        }
    }
    return int_force;
}

arma::vec PenningTrap::total_force(int i, int is_interact){
    /*
    Evaluates total internal and external forces for particle i
    */
    if (is_interact)
        return total_force_external(i) + total_force_particles(i);
//    std::cout << total_force_particles(i);
    return total_force_external(i);
}


void PenningTrap::evolve_RK4(double dt, int is_interact){
    /*
    Evolves the system on timestep dt with the 'RungeKutta4' method
    */
   
    // make copy of the particles so that the intitial values remains unchanged
    // get the number of particles
    int N = int(particles.size());
    std::vector<Particle> particles_copy;
    for (int i = 0; i < N; i++)
            particles_copy.push_back(particles[i]);
    
    std::vector<arma::vec> k1r, k2r, k3r, k4r;
    std::vector<arma::vec> k1v, k2v, k3v, k4v;
    
        
    // calculates the k's for r and v
    for (int i = 0; i < N; i++){
        
        // k1
        k1r.push_back(particles_copy[i].vel);
        k1v.push_back(total_force(i, is_interact)/particles_copy[i].mass);
        
        // update the copied particles possitions
        particles_copy[i].pos += k1r[i] * dt/2;
        particles_copy[i].vel += k1v[i] * dt/2;
       
    }
    
     for (int i = 0; i < N; i++){
        
        // k2
        k2r.push_back(particles_copy[i].vel);
        k2v.push_back(total_force(i, is_interact)/particles[i].mass);
        particles_copy[i].pos += k2r[i] * dt/2;
        particles_copy[i].vel += k2v[i] * dt/2;
       
    }
    
    
    for (int i=0;i<N;i++) {
        
        // k3
        k3r.push_back(particles_copy[i].vel);
        k3v.push_back(total_force(i, is_interact)/particles[i].mass);
        particles_copy[i].pos += k3r[i] * dt;
        particles_copy[i].vel += k3v[i] * dt;
    }
    
    for (int i=0;i<N;i++) {
        
        // k4
        k4r.push_back(particles_copy[i].vel);
        k4v.push_back(total_force(i, is_interact)/particles[i].mass);
    }
    
    for (int i = 0; i < N; i++){
        
        particles[i].pos += (k1r[i] + 2*k2r[i] + 2*k3r[i] + k4r[i]) * dt / 6;
        // update velocity
        particles[i].vel += (k1v[i] + 2*k2v[i] + 2*k3v[i] + k4v[i]) * dt / 6;
    }
}


void PenningTrap::evolve_forward_Euler(double dt, int is_interact) {
    /*
     Evolves the system on timestep dt with the 'Euler' method
     */
    
    for (int i = 0; i < particles.size(); i++){
        // update position
        particles[i].pos += particles[i].vel*dt;
        // update velocity
        particles[i].vel += total_force(i, is_interact) / particles[i].mass * dt;
    }
}
