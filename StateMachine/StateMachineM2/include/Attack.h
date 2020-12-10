#ifndef ATTACK_H
#define ATTACK_H
#include "MachineCommands.h"

TOP_STATE(Attack) {
public:
	Attack();
	IState* Handle(Machine & machine, std::any anything) override;
};


#endif