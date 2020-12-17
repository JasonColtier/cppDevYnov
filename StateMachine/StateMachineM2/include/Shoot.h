#ifndef SHOOT_H
#define SHOOT_H
#include "Attack.h"

SUB_STATE(Shoot,Attack) {
    public:
    Shoot() =default;
    IState* Handle(Machine & machine, std::any anything) override;
};


#endif