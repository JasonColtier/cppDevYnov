#pragma once
#include "AwsomeHero.h"
#include "TCustomHero.h"

class BasicCustomHero : public TCustomHero<AwsomeHero,BasicBehavior>
{
public:
	BasicCustomHero();
};

