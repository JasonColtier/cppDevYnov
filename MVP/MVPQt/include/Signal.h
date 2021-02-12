#pragma once

#include <atomic>
#include <map>
#include <functional>

//on fait notre propre signal / slot car on ne veut pas que le modèle / presenter hériente de QT 

template <typename... Args>
class Signal
{
public:
    Signal(): m_currentId(0)
    {
    }

    ~Signal()
    {
        DisconnectAll();
    }

    //constructeur par recopie
    Signal(const Signal& signal)
    {
        m_currentId = signal.m_currentId;
        for (auto&& [id,slot] : signal.m_slots) //pour parcourir une map
            m_slots[id] = slot;
    }

    //pas utile
    // Signal& operator=(const Signal& signal)
    // {
    //         
    // }

    //je veux que mes méthodes soient utilisées dans des méthodes const (getter / setter / constructeur...)
    //comment modifier une valeur dans une méthode const ?

    void Disconnect(const int& id) const
    {
        m_slots.erase(id);
    }

    void DisconnectAll() const
    {
        m_slots.clear();
        m_currentId = 0;
    }

    //pour ajouter des méthodes qui ne sont pas dans des classes
    //on attend une lambda avec des arguments qui retourne void
    int Connect(const std::function<void(Args ...)>& slot) const
    {
        m_slots.insert({++m_currentId, slot}); //constucteur de map, c'est le constructeur {}. Remplace le stdmake::pair
        return m_currentId;
    }

    //pour appeler des fonctions de classe : une fonction membre (12022021 / 17h20)
    template <typename T>
    int Connect(T* pInstance, void (T::*func)(Args ...)) const//il arrive à retrouver la fonction *func chez T. 
    {
        return Connect([=](Args... args)
        {
           (pInstance->*func)(args...);//je connecte la lambda à la fonction de ma classe passée en paramètre 
        });
    }

    //pour appeler des fonctions de classe const
    template <typename T>
    int Connect(T* pInstance, void (T::*func)(Args ...)const ) const
    {
        return Connect([=](Args... args)
        {
           (pInstance->*func)(args...);
        });
    }

    void operator()(Args... args)
    {
        for(auto slot : m_slots)
            slot.second(args...);
    }

private:
    mutable std::map<int, std::function<void(Args ...)>> m_slots;
    mutable std::atomic_int m_currentId;
};
