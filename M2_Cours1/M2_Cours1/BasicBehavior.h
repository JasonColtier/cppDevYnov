#pragma once

#include "IBehavior.h"

//h�rite de IBehavior

class BasicBehavior : public IBehavior//important mettre le public
{
public:
	void Action() override;//r�d�finition de la fonction Action
};

