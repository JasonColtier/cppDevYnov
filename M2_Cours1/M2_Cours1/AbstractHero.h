#pragma once

#include "IBehavior.h"
#include <memory>


//classe abstraite qui poss�de l'interface IBehavior
class AbstractHero
{
public:
	void Action();//mon h�ro poss�de une fonction action qui appellera l'interface
	virtual ~AbstractHero() = default;//destructeur virtuel. Pour toute classe purement virtuelle, il faut 

protected:
	std::unique_ptr<IBehavior> m_pBehavior;//interface qui dialogue avec la fonction Action de mon h�ro
};

