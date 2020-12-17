#ifndef RELOAD_H
#define RELOAD_H

#include "Attack.h"

SUB_STATE(Reload,Attack) {
    public:
    Reload() =default;
    IState* Handle(Machine & machine, std::any anything) override;
};

#endif
