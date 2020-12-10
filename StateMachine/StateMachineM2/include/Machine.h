#ifndef MACHINE_H
#define MACHINE_H
#include <functional>
#include <any>

#include "IState.h"

class Machine
{
public:
    Machine() : m_pCurrentState(nullptr)
    {
    }

    virtual ~Machine()
    {
        delete m_pCurrentState;
        m_pCurrentState = nullptr;
    }

    void Handle(std::any anything) //ceci n'est pas virtuel
    {
        m_function(anything);//on exectute n'importe quoi
    }

    IState* GetCurrentState() const
    {
        return m_pCurrentState;
    }

protected:
    std::function<void(std::any)> m_function; //void est le type de retour
    IState* m_pCurrentState;
};

#endif
