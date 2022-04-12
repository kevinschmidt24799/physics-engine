//
// Created by Kevin Schmidt on 3/31/22.
//
#ifdef __APPLE_CC__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#ifndef PHYSICS_SIMULATION_HPP
#define PHYSICS_SIMULATION_HPP

#include "particle.hpp"
#include "bond.hpp"
#include "matrix.hpp"
#include <vector>

class Simulation
{
public:
    std::vector<Particle> particles_;
    std::vector<Bond> bonds_;

    Matrix<3,3,float> eye_{};
    int leftx, lefty;
    bool left = false;

    void start(int argc, char **argv);
    virtual void draw();

    void display();
    virtual void mouse(int button, int state, int x, int y);
    virtual void motion(int x, int y);
    virtual void keys(unsigned char c, int x, int y);
    virtual void keysup(unsigned char c, int x, int y);

    void update(int i);

    int particle(float x, float y, float z);
    void bond(int p1, int p2);

    void run();
    void run(int cycles);

    void reset();
};


#endif //PHYSICS_SIMULATION_HPP
