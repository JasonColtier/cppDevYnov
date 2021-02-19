#pragma once
#include "ReferenceCounter.h"


//un pointeur partagé
//Comment ça fonctionne ?

//c'est un pointeur qui tant qu'il y a un objet qui pointe dessus , on le garde
//si on a plus rien qui pointe on le détruit

//on va faire un shared Ptr 

template <typename T>
class SharedPtr
{
public:


    SharedPtr() :
        m_pData(nullptr),
        m_pCounter(nullptr) //null car on peut créer un pointeur qui ne pointe sur rien
    {
    }

    explicit SharedPtr(const T& data) //constructeur dans lequel on lui passe un pointeur
        : m_pData(new T(data)) //new car on fait une nouvelle allocation !
          , m_pCounter(new ReferenceCounter())
    {
        m_pCounter->AddRef();
    }

    //consteucteur par copie d'un autre sharedptr
    SharedPtr(const SharedPtr& sharedPtr)
        : m_pData(sharedPtr.m_pData)
          , m_pCounter(sharedPtr.m_pCounter) //je copie la référenc existante
    {
        m_pCounter->AddRef();
    }


    //le destructeur
    ~SharedPtr()
    {
        ReleaseMemory();
    }

    double GetCount() const
    {
        
        return (m_pCounter == nullptr) ? 0 : m_pCounter->GetCount();
    }

    SharedPtr& operator=(const SharedPtr& sharedPrt)
    {
        ReleaseMemory();//car si on réaffecte il faut s'occuper de la donnée sur laquelle on pointait avant (s'il y en avait une)
        
        m_pData = sharedPrt.m_pData;
        m_pCounter = sharedPrt.m_pCounter;

        m_pCounter->AddRef();
        return *this;
    }

    T& operator*() const
    {
        return *m_pData; //je déréférence le pointer et ça retourne la valeur
    }

    T* operator->() const
    {
        return m_pData; //retourne le pointeur brut
    }

    T* Get() const
    {
        return m_pData; //idem que ->
    }

    //on reset le pointeur, il se déenregistre du pointeur et crée une nouvelle référence
    void Reset(T* pData)
    {
        m_pData = pData;
        m_pCounter->Release();
        m_pCounter = new ReferenceCounter();
    }

    void Swap(SharedPtr& p)
    {
        auto pTmp = p;
        p.m_pData = m_pData;
        p.m_pCounter = m_pCounter;

        m_pData = pTmp.m_pData;
        m_pCounter = pTmp.m_pCounter;
    }

    explicit operator bool() const
    {
        return m_pData != nullptr;
    }

private:
    
    void ReleaseMemory()
    {
        if(m_pCounter != nullptr)
            m_pCounter->Release(); //on décrémente le global

        //si plus rien de pointe sur notre donnée
        if (GetCount() == 0 && m_pData != nullptr)
        {
            delete m_pData;
            m_pData = nullptr;

            delete m_pCounter;
            m_pCounter = nullptr;
        }
    }
    
    
    ReferenceCounter* m_pCounter;
    T* m_pData; //on stocke le pointeur sur notre ojet évidemement
};
