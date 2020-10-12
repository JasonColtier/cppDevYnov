#include "TVector.h"

#include <iostream>
#include <ostream>


template <typename T>
TVector<T>::TVector()
{
	std::cout << "constructeur de TVector"<< std::endl;
    array = new T;//j'initialise mon tableau !
}

template <typename T>
void TVector<T>::push_back(T data)//ajout d'une donnée à la fin du tableau
{
    std::cout << "start pushback variable for length : "<<length << " and capacity : "<<capacity << std::endl;
    if (length + 1 > capacity){//si on a pas de place dans le tableau
        T* copy = array;//je copie mon talbeau
        capacity++;//il est plus long de 1
        array = new T[capacity];//je recrée mon tableau plus grand
        std::copy(copy, copy + length, array);//copie des anciennes valeurs dans mon nouveau tableau
        delete[] copy;//suppression de ce tableau dont on a plus besoin
	}
    array[length] = data;//insertion de la nouvelle valeur dans la case disponible
    length++;
}

template <typename T>
void TVector<T>::insert(T data, int pos)
{
    std::cout << "starting insert for length : " << length << " and capacity : " << capacity << " at pos" << pos << std::endl;
    T* copy = array;//je copie mon talbeau

	if (length + 1 > capacity) {//si on a pas de place dans le tableau
        capacity++;//il est plus long de 1
        array = new T[capacity];//je recrée mon tableau plus grand
    }
    int offset = 0;
    for(int i = 0;i<length + 1;i++)
    {
	    if(i + 1 == pos)
	    {
            array[i] = data;
            offset++;
	    }else
	    {
            array[i] = copy[i - offset];
	    }
    }
    delete[] copy;//suppression de ce tableau dont on a plus besoin
    length++;
}

template <typename T>
int TVector<T>::size()
{
    return length;
}

template <typename T>
T& TVector<T>::operator[](int pos)
{
    if (pos >= length) {
        std::cout << "Error: Array index out of bound";
        exit(0);
    }
    return array[pos];
}

template <typename T>
T& TVector<T>::at(int pos)
{
    if (pos >= length) {
        std::cout << "Error: Array index out of bound";
        exit(0);
    }
    return array[pos];
}

template <typename T>
T& TVector<T>::front()
{
    if (!empty())
        return array[0];
}

template <typename T>
T& TVector<T>::back()
{
    if (!empty())
        return array[length-1];
}

template <typename T>
bool TVector<T>::empty()
{
    if(size() == 0)
        return true;
    return  false;
}

template <typename T>
void TVector<T>::clear()
{
    std::fill_n(array, size(), 0);
    length = 0;
}

template <typename T>
void TVector<T>::print()
{
    std::cout << " -- print array ";

	for (int i = 0; i < size(); ++i)
	{
		std::cout << array[i] << " ";
	}
    std::cout << std::endl;
}

template <typename T>
void TVector<T>::printAdresses()
{
    std::cout << " -- print adresses ";

    for (int i = 0; i < size(); ++i)
    {
        std::cout << &array[i] << " ";
    }
    std::cout << std::endl;
}

template <typename T>
T & TVector<T>::iterator::operator*()
{
    return *ptr;
}

template <typename T>
typename TVector<T>::iterator& TVector<T>::iterator::operator++()
{
	ptr++;//le pointeur de cet itérateur est avancé de 1
	return (*this);//on retourne cet itérateur
}

template <typename T>
typename TVector<T>::iterator& TVector<T>::iterator::operator++(int i)
{
	typename TVector<T>::iterator temp = *this;
	ptr++;
	return temp;//avance le pointeur mais retourne l'itérateur avec l'ancien pointeur var++
}

template <typename T>
bool TVector<T>::iterator::operator==(iterator & it)
{
	return ptr == it.ptr;//si le pointeur de l'itérateur actuel est le même que celui passé en paramètre
}

template <typename T>
bool TVector<T>::iterator::operator!=(iterator & it)
{
	return ptr != it.ptr;
}

template <typename T>
typename TVector<T>::iterator TVector<T>::iterator::operator+(int add)
{
	typename TVector<T>::iterator tmp(ptr + add);//je crée un itérateur en partant de notre pointeur et en lui ajoutant X
	return  tmp;
}

template <typename T>
typename TVector<T>::iterator TVector<T>::iterator::operator-(int sub)
{
	typename TVector<T>::iterator tmp(ptr - sub);
	return  tmp;
}

template <typename T>
typename TVector<T>::iterator TVector<T>::begin()
{
    return iterator(array);//retourne un iterator pointant vers le premier élément
}

template <typename T>
typename TVector<T>::iterator TVector<T>::end()
{
    return iterator(array + length);//retourne un élément après la fin du tableau
}

template <typename T>
typename TVector<T>::iterator TVector<T>::erase(iterator pos)
{
	std::cout << "address to remove is : " << &*pos <<std::endl;
    //iterator tmp = pos;
    //tmp++;
    //length--;//il est plus court de 1

    //std::copy(tmp, end(), pos);
	//

	//ici (*this) est l'itérator déréférencé 

	
	int i = 0;
	auto it = (*this).begin();
	auto end = (*this).end();

	for (it; it != pos; it++, i++);

	for (auto it = pos + 1; it != end; it++, i++)
		array[i] = array[i + 1];

	length--;
	
    return pos;

}
