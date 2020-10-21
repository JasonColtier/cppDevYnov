#pragma once
#include "AbstractHero.h"
#include <iostream>

//classe template avec  2 param�tres : un pour savoir de quel h�ro on h�rite et un pour savori quel behavior on utilise
template<class HeroType = AbstractHero, typename BehaviorType = IBehavior>
class TCustomHero : public HeroType
{
	static_assert(std::is_base_of<IBehavior, BehaviorType>::value,
		"error ! type T should inherit from Ibehavior");

	static_assert(std::is_base_of<AbstractHero, HeroType>::value,
		"error ! type T should inherit from AbstractHero");

	TCustomHero()
	{
		//this car normalement on est d�ja attribu�
		this->m_pBehavior = std::make_unique<BehaviorType>();//affecte le type de behavior en fonction de ce qu'on passe en T !
		std::cout << "new THero " << std::endl;
	}
};

