#pragma once
#include "BasicBehavior.h"
#include "CurrentBehavior.h"
#include "Hero.h"
#include "IBehavior.h"
#include "THero.h"
#include "iostream"

class AwsomeHero : public THero<CurrentBehavior>//j'indique le paramètre ici au compilateur !
{
	
};

