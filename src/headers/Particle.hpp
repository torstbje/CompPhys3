#ifndef PARTICLE_HPP
#define PARTICLE_HPP

class Particle{

private:

public:

    double charge, mass;
    arma::vec pos, vel;

    Particle(double, double, arma::vec, arma::vec);
    std::string get_string();
};

#endif
