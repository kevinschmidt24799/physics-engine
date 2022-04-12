//
// Created by Kevin Schmidt on 3/30/22.
//
#include "particle.hpp"
#ifndef PHYSICS_BOND_HPP
#define PHYSICS_BOND_HPP
#include <math.h>

struct Bond
{
    Particle * p1_;
    Particle * p2_;
    const float length_;
    float k_ = 1;

    Bond(Particle * p1, Particle * p2): p1_(p1), p2_(p2),
    length_(sqrtf(powf(p1_->p.x()-p2_->p.x(), 2)+powf(p1_->p.y()-p2_->p.y(), 2)+powf(p1_->p.z()-p2_->p.z(), 2))){}

    void set_forces();
};


#endif //PHYSICS_BOND_HPP
