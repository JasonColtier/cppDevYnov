#ifndef HERO_H
#define HERO_H
#include "HeroMachine.h"


class Hero
{
public:

    //on pourrait utiliser des stduniqueptr
    
    Hero() : m_pMachine(new HeroMachine())
    {
        
    }

    //simulation
    void Run()
    {
        while (true)
        {
            Handle();
        }
    }


private:
    void Handle()
    {
        m_pMachine->Handle("");
    }
    
    HeroMachine* m_pMachine;

    
};


#endif