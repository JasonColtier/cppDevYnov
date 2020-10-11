#pragma once

#include "IBehavior.h"

//hérite de IBehavior

class CurrentBehavior : public IBehavior
{
public:
	void Action() override;//rédéfinition de la fonction Action
};

