#pragma once
#include <cassert>
#include <iostream>
#include <ostream>
#include <algorithm>

template <typename T>
class TVector
{
private:
	T* array; //le tableau de mes valeurs de type T
	size_t length = 0; //le nombre de valeurs dans mon array
	size_t capacity = 0; //la taille du tableau


	//première version de mon itérateur

	//class iterator // un iterator permet de parcourir le vector
	//{
	//private:
	//	T* ptr;// un  iterator est composé d'un pointeur pointant vers l'adresse d'une des variable du vecteur
	//public:
	//	iterator(T* item) :ptr(item)
	//	{
	//		std::cout << "iterator created ! pointing to :" << *item << std::endl;
	//	}// constructeur de l'itérateur initialisant son pointeur sur l'adresse de la variable du vector
	//};

	using Iterator = T*;
	using ConstIterator = const T*;


	friend std::ostream& operator<<(std::ostream& os, const TVector<int>& vector);//à faire en variante pour tous les type que l'on veut proposer


public:


	//constructeur basique
	TVector()
	{
		std::cout << "new vector created" << std::endl;
		array = new T;//j'initialise mon tableau !
	}

	//constructeur prenant en paramètre la taille du tableau
	TVector(const size_t& size)//ici size_t est approprié car cela correspond à une taille de tableau. De plus size_t >= 0
	{
		if (size > 0)
		{
			array = new T[size];
			capacity = size;
			std::cout << "new vector created with size " << size << std::endl;
		}
		else
		{
			std::cout << "size cant be 0 !";
		}
	}

	//initialisation de mon vecteur en prenant une liste de valeurs
	TVector(const std::initializer_list<T>& list)
	{
		array = new T[list.size()];//vecteur de la taille de la list
		length = list.size();
		capacity = list.size();

		std::cout << "new vector created with ( ";

		size_t index = 0;
		for (T element : list)
		{
			array[index] = element;
			index++;
			std::cout << element << " ";

		}
		std::cout << " )" << std::endl;
	}


	//destructeur
	~TVector()
	{
		delete[] array;//je delete mon array
		array = nullptr;
		length = 0;
		capacity = 0;
	}


	/*
	 * FONCTIONS
	 */
	ConstIterator Begin() const { return ConstIterator(array); }//retourne pointeur vers le premier élément
	Iterator Begin() { return Iterator(array); }//retourne pointeur vers le premier élément
	ConstIterator End() const { return ConstIterator(array + length); }//retourne un pointeur vers le dernier élément
	Iterator End() { return Iterator(array + length); }//retourne un pointeur vers le dernier élément

	T& Front() {//retourne le premier élément du tableau
		if (length !=0)
			return array[0];
	}

	T& Back()//retourne le dernier élément du tableau
	{
		if (length !=0)
			return array[length - 1];
	}

	T& At(const size_t& pos)//retourne l'élément à la position pos du tableau
	{
		if (pos >= length) {
			std::cout << "Error: Array index out of bound";
			return array[0];
		}
		return array[pos];
	}

	//la taille de mon tableau de valeurs
	int Size()
	{
		return length;
	}

	//tri des valeurs du tableau
	void Sort()
	{
		std::sort(array, array + length);
	}

	bool Empty()//est ce que mon tableau est vide ?
	{
		if (length == 0)
			return true;
		return  false;
	}

	void Clear()//écrase toutes les valeurs du tableau
	{
		std::fill_n(array, length, 0);
		length = 0;
	}

	//ajout d'une valeur à la fin
	void Push_back(const T& data)
	{
		std::cout << "start pushback of " << data << " for length : " << length << " and capacity : " << capacity << std::endl;
		if (length + 1 > capacity) {//si on a pas de place dans le tableau
			Reserve(1);
		}
		array[length] = data;//insertion de la nouvelle valeur dans la case disponible
		length++;
	}

	//ajout d'une liste à la fin
	void Push_back(const std::initializer_list<T>& list)
	{
		if (length + list.size() > capacity)
		{
			Reserve(list.size());
		}

		size_t index = length;
		for (T element : list)
		{
			array[index] = element;
			index++;
		}
		length += list.size();
	}

	//fonction pour allouer plus de mémoire si mon tableau est trop petit
	void Reserve(size_t size)
	{
		T* copy = array;//je copie mon talbeau
		capacity += size;//il est plus long de 1
		array = new T[capacity];//je recrée mon tableau plus grand
		std::copy(copy, copy + length, array);//copie des anciennes valeurs dans mon nouveau tableau
		delete copy;//suppression de ce tableau dont on a plus besoin
	}

	//insertion d'une valeur à une position, pourrait être améliorée pour prendre une liste de valeurs au lieu d'une comme le pushback et utiliser les iterateurs
	void Insert(const T& data, const int& pos)
	{
		std::cout << "starting insert for length : " << length << " and capacity : " << capacity << " at pos " << pos << std::endl;
		T* copy = new T[length];
		std::copy(array, array + length, copy);//je copie mon talbeau

		if (length + 1 > capacity) {//si on a pas de place dans le tableau
			capacity++;//il est plus long de 1
			delete array;
			array = new T[capacity];//je recrée mon tableau plus grand
		}
		int offset = 0;
		for (int i = 0; i < length + 1; i++)
		{
			if (i + 1 == pos)//si on est à l'endroit de la nouvelle valeur je la copie
			{
				array[i] = data;
				offset++;
			}
			else//sinon je copie les valeurs de l'ancien tableau
			{
				array[i] = copy[i - offset];
			}
		}
		delete copy;//suppression de ce tableau dont on a plus besoin
		length++;
	}

	//retourne la distance entre deux itérateurs
	static size_t Distance(ConstIterator it1,ConstIterator it2)
	{
		return static_cast<size_t>((it1 - it2) * sizeof(it1) / sizeof(T));
	}


	//pourrait aussi fonctionner avec l'index mais on va utiliser l'iterateur pour pratiquer
	void Erase(ConstIterator pos)
	{
		std::cout << "value to remove is : " << *pos << std::endl;
		assert(length > 0 && array != nullptr && "No data in array");
		assert(pos != nullptr && "Bad iterator");

		int i = 0;
		auto it = Begin();
		auto end = End();

		for (it; it != pos; it++, i++);//j'incrémente mon it et i jusqu'à tomber sur pos

		for (auto it = pos + 1; it != end; it++, i++)//à partir de là je copie avec un offset de 1
			array[i] = array[i + 1];

		length--;

	}


	/*
	* SURCHARGE DES OPERATEURS
	*/

	TVector<T>& operator=(TVector<T>& vector)
	{
		length = vector.length;//ma taille est celle du vecteur à copier
		capacity = vector.length;//idem pour ma capacité, car seulement ses valeurs nous interessent
		array = new T[vector.length];
		std::copy(vector.Begin(), vector.End(), this->Begin());//copie des valeurs à l'aide des pointeurs Begin et End
		return *this;
	}

	T& operator[](int pos)
	{
		if (pos >= length) {
			std::cout << "Error: Array index out of bound";
			exit(0);
		}
		return array[pos];
	}

	T& operator*()
	{
		return *this;
	}

};

std::ostream& operator<<(std::ostream& os, const TVector<int>& vector)
{
	os << "(";
	for (TVector<int>::ConstIterator it = vector.Begin(); it != vector.End(); it++)
	{
		os << " " << *it;
	}
	return os << ")";
};


