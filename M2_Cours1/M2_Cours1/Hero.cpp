#include "Hero.h"
#include "BasicBehavior.h"//obligé de l'include pour s'en servir et dire quelle behavior on choisit
#include "CurrentBehavior.h"


Hero::Hero()//dans le constructeur
{
	// Create a new unique_ptr with a new object.
	m_pBehavior = std::make_unique<BasicBehavior>();//je dis que je choisis BasicBehavior
	
}

