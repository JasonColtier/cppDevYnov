#pragma once


//Interface composée de fonctions virtual
class IBehavior
{
public:
	virtual ~IBehavior() = default;//destructeur virtuel
;	virtual void Action() = 0;//fonction virtuelle, on met 0 pour dire qu'elle doit forcément être implémentée
};

