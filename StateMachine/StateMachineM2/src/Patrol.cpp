#include "Patrol.h"
#include <iostream>

IState* Patrol::Handle(Machine& machine, std::any anything)
{
    std::cout << "patrol" << std::endl;
    return Idle::Handle(machine,anything); //on délègue au parent
}
