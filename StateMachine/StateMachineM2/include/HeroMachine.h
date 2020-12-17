#ifndef HEROMACHINE_H
#define HEROMACHINE_H
#include "MachineCommands.h"
#include "Patrol.h"
#include "Signal.h"

//s'occupe de changer d'état
MACHINE(HeroMachine)
{
public:
    HeroMachine()
    {
        INIT_STATE(Patrol);

        //lambda c++
        m_function = [this](std::any anything)
        {

            m_signal(anything);
            
            //on récup l'état courant après réaction Handle. Si ce nouvel état n'est pas nul, on change d'état
            if (const auto pState = m_pCurrentState->Handle(*this, anything); pState != nullptr && pState !=
                m_pCurrentState)
            {
                delete m_pCurrentState;
                //on supprime l'ancien état (on supprime la donnée qui était associée à notre pointeur)
                m_pCurrentState = pState; //on set notre nouvel état
            }
        };
    }

    //18h25
    Signal<std::any>& GetSignal()
    {
        return m_signal;
    }

private:
    Signal<std::any> m_signal;//comme le ObserverPatern !
};


#endif
