#include "Reload.h"
#include <iostream>

#include "Shoot.h"

IState* Reload::Handle(Machine& machine, std::any anything)
{
    m_ammo = g_ammo;//on a rechargé et on revient à 10
    std::cout << "Reload : " <<m_ammo<< std::endl;
    return new Shoot();

    //quand on recharge on met à jour les muns
}
