//
// Created by Kevin Schmidt on 3/30/22.
//

#ifndef PHYSICS_PARTICLE_HPP
#define PHYSICS_PARTICLE_HPP
#include "math.h"
#include "matrix.hpp"

using Point = Matrix<3, 1>;

Point operator* (Point const & p1, Point const & p2);

struct Particle
{
    Point p;
    Point d;

    bool touching = false;

    float mass_ = 1;
    Point f;

    Particle(Point const & in): p(in){}

    void move();
};

float distance(Particle const & p1, Particle const & p2);
#endif //PHYSICS_PARTICLE_HPP
