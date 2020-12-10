#ifndef MACHINECOMMANDS_H
#define MACHINECOMMANDS_H
#include "Machine.h"
#include "IState.h"

// macro pour création de classes
#define TOP_STATE(state)\
	class state : public IState

#define SUB_STATE(state, parent) \
	class state : public parent

#define MACHINE(name) \
	class name : public Machine

#define INIT_STATE(state) \
	m_pCurrentState = new state();



#endif
