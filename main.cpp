
#include "simulator.h"
#include <iostream>
#include <stdio.h>

int main(int argc, char** argv)
{
    Simulator sim;
    sim.load(argv[1]);
    sim.run();
    return 0;
}
