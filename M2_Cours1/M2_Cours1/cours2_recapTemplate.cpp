#include "cours2_recapTemplate.h"
#include <iostream>


double Add(const double& lhs, const double& rhs)
{
	return  lhs + rhs;
}

int Add(const int& lhs,const int& rhs)
{
	return lhs + rhs;
}

//fonction tempalte
template<typename T>
T TAdd(const T& lhs, const T& rhs)
{
	std::cout << "template"<<std::endl;
	return  lhs + rhs;
}


//avec deux types différents
template<typename T,typename P>
T TAddDIff(const T& lhs, const P& rhs)
{
	std::cout << "template" << std::endl;
	return  lhs + rhs;
}


template<int T>
//template<int T = 3>//valeur par défaut 
int TAddConst()//pas besoin de mettre de paramètres. Le résultat de ce calcul est donné à la compilation
{
	//utilise le nonType parameter = le type est déja déffinit
	//si on a des erreurs ce sera à la compilation.

	static_assert(T < 4);// on peut aussi faire ça !
	
	return T + 3;
}

template<typename T>
class TPoint
{
	static_assert(std::is_pod<T>::value);
public:
	TPoint(const T& x,const T& y) : m_x(x),m_y(y)//initialisation des variables 
	{
		
	}
	T GetX() const
	{
		return m_x;
	}
	T GetY() const
	{
		return m_y;
	}
	
private:
	T m_x;
	T m_y;
};


//à ne jamais faire !
int* ATTENTION()
{
	int p = 3;//nouvelle variable créé dans la fonction
	return &p;
}


template<typename... Args>//fonction variadique (ne marche que en c++ 2017)
void Display(int t, Args... args)//le premier arg de type int. Il faut forcément cette première variable pour faire l'assignation. Peut être de type T
{
	std::cout << t << std::endl;//à chaque fois le t prend la valeur d'un paramètre
	if constexpr (sizeof...(args)> 0){//si on a des paramètres 
		Display(args...);//on repasse dans la fonction pour traiter les autres paramètres moins celui qu'on vient de traiter
	}
}

int cours2_main()
{
	const auto result = TAddConst<3>(); 
	
	//auto result = TAddDIff(3, 5.0);//passe par template diff
	//auto result = TAdd(3, 5);//passe par template
	//auto result = Add(3, 5);//passe par int
	//auto result = Add(3.0, 5.0); // passe par double
	std::cout << result << std::endl;

	TPoint<int> ptInt(3, 6);
	//TPoint<int> ptInt("v", "y"); // passe dans le static asset !
	std::cout << typeid(ptInt.GetX()).name() << std::endl;
	std::cout << typeid(ptInt.GetY()).name() << std::endl;

	Display(4, 5, 8);
	
	return 0;
}