#ifndef ATTACK_H
#define ATTACK_H
#include "MachineCommands.h"

constexpr  int g_ammo = 10; //ça veut dire que cet élément là est résolu à la compilation
//différent du define qui est un remplacement syntastique (à éviter)

TOP_STATE(Attack)
{
public:
    Attack();
    IState* Handle(Machine& machine, std::any anything) override;

protected:
    int m_ammo;//est reset quand on passe à idle
    //pourrait être géré par le héro
};


#endif
