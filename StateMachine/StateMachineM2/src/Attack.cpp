#include "Attack.h"
#include <iostream>

#include "Odometric.h"
#include "Patrol.h"



Attack::Attack()
    : m_ammo(g_ammo)
{
}

IState* Attack::Handle(Machine& machine, std::any anything)
{
    std::cout << "Attack " << std::endl;

    const auto odometry = std::any_cast<Odometric>(anything);
    if (odometry == Odometric::EnemyDead)
    {
        std::cout << "Enemy dead " << std::endl;
        return new Patrol();
    }

    //tant que l'ennemi n'est pas mort on reste dans la boucle
}
