#ifndef PATROL_H
#define PATROL_H

#include "Idle.h"

SUB_STATE(Patrol,Idle) {
    public:
    Patrol() =default;
    IState* Handle(Machine & machine, std::any anything) override;
};

#endif
