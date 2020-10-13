#pragma once
#include <ostream>

#include "AbstractHero.h"
#include "BasicBehavior.h"

template <typename T>
class THero : public AbstractHero
{

	
public:
	static_assert(std::is_base_of<IBehavior, T>::value,
		"error ! type T should be inherit from Ibehavior");

	THero(){ std::cout << "new THero "<<std::endl; }
	

};

