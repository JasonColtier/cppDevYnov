#pragma once
#include "BasicBehavior.h"
#include "Hero.h"
#include "IBehavior.h"
#include "THero.h"
#include "iostream"

class AwsomeHero : public THero<BasicBehavior>
{
public:
	AwsomeHero(){ m_pBehavior = std::make_unique<BasicBehavior>();}
};

