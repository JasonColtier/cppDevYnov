#pragma once
#include <ostream>
#include <iostream>

#include "AbstractHero.h"
#include "IBehavior.h"


//cette template hérite de abstract hero
template <typename BehaviorType = IBehavior>//typename initialisé à IBehavior
class THero : public AbstractHero
{

	
public:
	static_assert(std::is_base_of<IBehavior, BehaviorType>::value,
		"error ! type T should inherit from Ibehavior");

	THero()
	{
		m_pBehavior = std::make_unique<BehaviorType>();//affecte le type de behavior en fonction de ce qu'on passe en T !
		std::cout << "new THero "<<std::endl;
	}
	
};

