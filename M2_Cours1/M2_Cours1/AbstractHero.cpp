#include "AbstractHero.h"

// j'implémente la classe Action de mon interface

void AbstractHero::Action()
{
	m_pBehavior->Action();//je dis que quand j'appelle la fonction Action de mon héro ça appelle la fonction Action de mon interface
}
