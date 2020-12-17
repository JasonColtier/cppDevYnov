#ifndef HERO_H
#define HERO_H
#include <array>
#include <iostream>


#include "HeroMachine.h"
#include "Odometric.h"

constexpr int g_loopCounter = 25;

class Hero
{
public:

    //on pourrait utiliser des stduniqueptr

    Hero()
        : m_pMachine(new HeroMachine()),
          m_sensorState(Odometric::Ras),
          m_index(0),
          m_loopCounter(g_loopCounter)
    {
        //ce qui va se passer dans l'histoire
        m_simulation = {{Odometric::Ras, Odometric::EnemyDetected, Odometric::EnemyDead, Odometric::Ras}};

        //on crée une connexion à la machine
        m_pMachine->GetSignal().Connect([this](const auto& odometry)
        {
            const auto newState = std::any_cast<Odometric>(odometry);


            switch (newState)
            {
            case Odometric::Ras:
                std::cout << "         # RAS #         " << std::endl;
                break;

            case Odometric::EnemyDetected:
                std::cout << "         # EnemyDetected #         " << std::endl;
                break;

            case Odometric::EnemyDead:
                std::cout << "         # EnemyDead #         " << std::endl;
                break;

            default:
                std::cout << "         # default #         " << std::endl;
            }

            if (m_sensorState == newState)
            {
                //si on a pas changé d'état 18h29, on va la forcer à changer d'état. On test le comportement
                --m_loopCounter;
            }

            if (m_loopCounter <= 0)
            {
                m_loopCounter = g_loopCounter;
                ++m_index; //on passe à l'état suivant

                if (m_index >= m_simulation.size())
                {
                    m_index = 0; //on reboucle
                }
            }

            m_sensorState = newState;
        });
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
        m_pMachine->Handle(m_simulation[m_index]);
    }

    HeroMachine* m_pMachine;
    Odometric m_sensorState; //ce qu'il détecte, l'état actuel

    //tableau à taille fixe
    std::array<Odometric, 4> m_simulation;
    int m_index; //où on en est dans l'histoire

    int m_loopCounter;
};


#endif
