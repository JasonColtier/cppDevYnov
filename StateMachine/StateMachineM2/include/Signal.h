#ifndef SIGNAL_H
#define SIGNAL_H
#include <atomic>
#include <functional>
#include <map>

//le signal pour envoyer des infos au héro
//18h24

template<typename ...Args>
class Signal
{
    using Slot = std::function<void(Args...)>;//1 slot = 1 fonction
    //cette ligne crée un alias. écrire slot revient à écrire ça ...
    
public:
    Signal()
        : m_currentId(0)//au début le signal est de 0
    {
        
    }

    ~Signal()
    {
        DisconnectAll();
    }

    Signal(const Signal& signal)//constructeur par recopie
    {
        m_currentId = signal.m_currentId;//on récupère son id actuelle
        m_slots = signal.m_slots;//et tous ces éléments
    }

    Signal& operator=(const Signal& signal)
    {
        DisconnectAll();
        m_currentId = signal.m_currentId;//on récupère son id actuelle
        m_slots = signal.m_slots;//et tous ces éléments
        return *this;
    }

    //attribue un slot à une fonction
    int Connect(const Slot& slot) const
    {
        m_slots.insert({++m_currentId,slot});
        return m_currentId;
    }

    //on va permettre d'associer un pointeur de fonction apaprtenant à notre classe
    //18h04 le 11/12/2020
    //connecte une méthode d'une classe (fonction non constante)

    //T::* funct = le pointeur de fonction
    //18h11
    //la labda expression c'est un slot au final
    
    template<typename T>
    int Connect(T* pInstance, void (T::* func)(Args...)) const
    {
        return Connect([=](Args... args)//labda expression c++. Capture le contexte (tous les arguments) par copie    [&] pour une capture par ref
        {
            (pInstance->*func(args...));
        });
    }

    template<typename T>
    int Connect(T* pInstance, void (T::* func)(Args...) const)//pour que ça marche aussi avec une fonction const
    {
        return Connect([=](Args... args)
        {
            (pInstance->*func(args...));
        });
    }
    

    //on fait la fonction de chaque slot
    void operator()(Args... args)
    {
        for(auto slot : m_slots)
        {
            slot.second(args...);
        }
    }

    void Disconnect(const int& id) const
    {
        m_slots.erase(id);
    }

    void DisconnectAll()
    {
        m_slots.clear();//car pas de ptr
        m_currentId = 0;
    }

private:
    mutable std::atomic_int m_currentId;
    //mutable pour que la fonction connect puisse être const
    //pour être multi threadable
    //une ionstruction atomique ne peut pas être interrompu par un autre processus.
    //si on a deux threads qui font une connection au même slot en même temps ça pête
    //la variable atomique gère le mutex
    
    mutable std::map<int,Slot>m_slots;//associe une fonction à une ID
    
};

#endif

