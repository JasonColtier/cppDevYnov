#include "Hide.h"
#include "Reload.h"
#include <iostream>

IState* Hide::Handle(Machine& machine, std::any anything)
{
    std::cout << "hide" << std::endl;
    return new Reload();
}
