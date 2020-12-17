#include "Idle.h"
#include <iostream>
#include "Odometric.h"
#include "Shoot.h"

IState* Idle::Handle(Machine& machine, std::any anything)
{
    std::cout << "Idle" << std::endl;

    //dès qu'il détecte un ennemi il attaque

    const auto odometricState = std::any_cast<Odometric>(anything);

    switch (odometricState)
    {
    case Odometric::EnemyDetected:
        {
            std::cout << "Switch to Attack mode" << std::endl;
            return new Shoot();
        }
    default:
        return this;
    }
}
