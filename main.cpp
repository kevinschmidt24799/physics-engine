#include <iostream>
#include <vector>
#include "particle.hpp"
#include "simulation.hpp"
#include "bond.hpp"
#include <unistd.h>

int main(int argc, char **argv)
{
    Simulation s;
    s.reset();
    s.start(argc, argv);

}
