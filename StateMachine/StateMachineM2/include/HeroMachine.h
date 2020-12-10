#ifndef HEROMACHINE_H
#define HEROMACHINE_H
#include "MachineCommands.h"


MACHINE(HeroMachine)
{
public:
    HeroMachine()
    {
        // INIT_STATE();

        //lambda c++
        m_function = [this](std::any anything)
        {
            //on récup l'état courant après réaction Handle. Si ce nouvel état n'est pas nul, on change d'état
            if(const auto pState = m_pCurrentState->Handle(*this); pState != nullptr && pState != m_pCurrentState)
            {
                delete m_pCurrentState;//on supprime l'ancien état (on supprime la donnée qui était associée à notre pointeur)
                m_pCurrentState = pState;//on set notre nouvel état
            }
        };
    }
};


#endif
