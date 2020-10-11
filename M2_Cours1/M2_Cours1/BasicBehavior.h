#pragma once

#include "IBehavior.h"

//hérite de IBehavior

class BasicBehavior : public IBehavior//important mettre le public
{
public:
	void Action() override;//rédéfinition de la fonction Action
};

