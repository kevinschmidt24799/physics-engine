//
// Created by Kevin Schmidt on 3/30/22.
//

#include "bond.hpp"



void Bond::set_forces()
{
    Point d = p2_->p - p1_->p;

    float k_displacement = 0.002*k_ * (sqrtf(d.x() * d.x() + d.y() * d.y() + d.z() * d.z()) - length_);//positive = stretch

    p1_->f = p1_->f + (d*k_displacement);
    p2_->f = p2_->f - (d*k_displacement);

}