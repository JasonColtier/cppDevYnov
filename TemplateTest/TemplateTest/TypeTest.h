#pragma once


inline bool StringCompare(const char* pLhs, const char* pRhs)
{
    size_t i = 0;

    //ici voir comment comparer efficacement les deux strings : vidéo à 18h50;

    //faire des && entre deux octets

    while (pLhs[i] != '\0' && pRhs[i] != '\0') // ce symbole marque la fin d'une chaine de caractères
    {
        if (pLhs[i] != pRhs[i])
            return false;

        ++i;
    }

    return true;
}


template <class T, T Val>
struct IntegralConstant
{
    static constexpr T value = Val;
    using ValueType = T;
    using Type = IntegralConstant;

    constexpr explicit operator ValueType() const noexcept
    {
        return value;
    }

    constexpr ValueType operator()() const noexcept
    {
        return value;
    }
};

struct FalseType : IntegralConstant<bool, false>
{
};

struct TrueType : IntegralConstant<bool, true>
{
};

template <typename A, typename B>
struct IsSame : FalseType
{
};

template <typename A>
struct IsSame<A, A> : TrueType
{
};


template <typename... Ts>
struct MakeVoid
{
    using Type = void;
};

template<typename... Ts>
using VoidT = typename MakeVoid<Ts...>::Type;