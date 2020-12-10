#ifndef HIDE_H
#define HIDE_H
#include "Attack.h"

SUB_STATE(Hide,Attack) {
    public:
    Hide() =default;
    IState* Handle(Machine & machine, std::any anything) override;
};


#endif