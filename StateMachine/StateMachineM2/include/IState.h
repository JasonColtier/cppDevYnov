#ifndef ISTATE_H
#define ISTATE_H
#include <any>

class Machine;

class IState
{
public:
	virtual ~IState() = default;
	virtual IState* Handle(Machine& machine, std::any anything) = 0;
};

#endif