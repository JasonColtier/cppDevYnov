#include "Idle.h"
#include <iostream>

IState* Idle::Handle(Machine& machine, std::any anything)
{
    std::cout << "Idle" << std::endl;
    
}
