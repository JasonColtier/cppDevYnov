#pragma once
#include <atomic>

//il faut que notre conteur soit thread safe
//il va compter les références de nos smart pointers
//classe à part car peut être utilisé en dehors du sharedptr

class ReferenceCounter
{
public:
    ReferenceCounter() : m_count(0)
    {
            
    }

    ~ReferenceCounter() = default;

    
    void AddRef()
    {
        ++ m_count;
    }

    void Release()
    {
        -- m_count;
    }

    //conversion implicite en double je pense
    double GetCount() const
    {
        return m_count;
    }

private:
    //unsigned int assez grand
    std::atomic_uint64_t m_count;
};
