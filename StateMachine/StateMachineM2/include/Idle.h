#ifndef IDLE_H
#define IDLE_H
#include "MachineCommands.h"

TOP_STATE(Idle){
public:
	Idle() = default;
	IState* Handle(Machine & machine,std::any anything) override;
};
	

#endif