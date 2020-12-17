#include "Shoot.h"
#include <iostream>
#include "Hide.h"
#include "Odometric.h"

IState* Shoot::Handle(Machine& machine, std::any anything)
{
    --m_ammo;//on utilise une munition
    
    std::cout << "Shoot : ammo = " <<m_ammo<< std::endl;
    if(m_ammo > 0)//on continue de tirer on a encore des mun
    {
        if(std::any_cast<Odometric>(anything) == Odometric::EnemyDead)
        {
            return Attack::Handle(machine,anything);//le parent gère ce qu'on doit faire dans ce cas là
        }
        return this;//sinon on continue de tirer
    }
    //si on a plus de mun on se cache
    return new Hide();
}
