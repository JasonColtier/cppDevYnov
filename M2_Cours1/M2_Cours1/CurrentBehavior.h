#pragma once

#include "IBehavior.h"

//h�rite de IBehavior

class CurrentBehavior : public IBehavior
{
public:
	void Action() override;//r�d�finition de la fonction Action
};

