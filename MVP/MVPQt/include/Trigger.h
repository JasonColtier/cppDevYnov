#pragma once

#include "Signal.h"
#include <any>
#include <functional>


//on refait notre propre Observable

using EventSignal = Signal<const std::any&>; //un alias

template <typename T>
class Trigger
{
public:
    Trigger() = default;

    //si on passe pour la copie un trigger
    Trigger(const Trigger& trigger): m_value(trigger.m_value)
    {
    }

    //si on passe direct une valeur
    explicit Trigger(const T& value): m_value(value)
    {
    }

    ~Trigger() = default;

    Trigger& operator=(const T& value)
    {
        if(m_value != value)
        {
            m_value = value;
            Notify();
        }
        return *this;
    }

    Trigger& operator=(const Trigger& trigger)
    {
        if(m_value != trigger.m_value)
        {
            m_value = trigger.m_value;
            Notify();
        }
        return *this;
    }

    operator T()const//operateur de cast, différent de celui ()
    {
        return m_value;
    }

    void SetNoTrig(const Trigger& trigger)//pour initialiser par exemple et éviter boucles infinies
    {
        if(m_value != trigger.m_value)
        {
            m_value = trigger.m_value;
            //pas de notify
        }
    }

    void SetNoTrig(const T& value)
    {
        if(m_value != value)
        {
            m_value = value;
        }
    }

    //pourrait être privé, surtout utile pour du polymorphisme
    void Connect(const std::function<void(const std::any&)>& func) const
    {
        m_signal.Connect(func);
    }

    void ConnectTyped(const std::function<void(const T&)>& func) const
    {
        const auto funcAny = [func](const std::any& lhs)//left hand side, on pourrait l'appeler any
        {
            const auto element = std::any_cast<T>(lhs);//je crée une lambda qui appelle ma fonction typée
            func(element);
        };
        m_signal.Connect(funcAny);
    }

private:

    //appelé à chaque changement de notre trigger
    void Notify()
    {
        m_signal(m_value);
    }

    T m_value;
    mutable EventSignal m_signal;
};
