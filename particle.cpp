//
// Created by Kevin Schmidt on 3/30/22.
//

#include <cmath>
#include "particle.hpp"

void Particle::move()
{
    d = d * 0.9995;
    d = d + (f / mass_);
    p = p + (d / 1000);

    if(p.y() < 0)
    {
        p.y() = 0;
        d.y() = 0;
    }

    f = 0;

}

float distance(Particle const & p1, Particle const & p2)
{

    auto d = p1.p - p2.p;

    return sqrtf(d.x()*d.x() + d.y()*d.y() + d.z()*d.z());
}

Point operator* (Point const & p1, Point const & p2)
{
    return Point{{p1.data_[0][0]*p2.data_[0][0]}, {p1.data_[1][0]*p2.data_[1][0]}, {p1.data_[2][0]*p2.data_[2][0]}};
}