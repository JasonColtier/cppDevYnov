#include "TList.h"
#include <iostream>


template <typename T>
TList<T>::TList()
{
	length = 0;
	head.prev = &head;//j'initialise la première node de ma liste à elle même en reference
	head.next = &tail;//sera modifiée après la première valeur ajoutée
	tail.next = &tail;//idem pour la fin 
	tail.prev = &head;
	std::cout << "list constructed ! head adress is "<<&head<<std::endl;
	std::cout << "list constructed ! tail adress is "<<&tail<<std::endl;
	//std::cout << "list constructed ! tail prev is "<<tail.prev<<std::endl;
	//comme un sandwich ! 
}

template <typename T>
int TList<T>::size()
{
	return length;
}

template <typename T>
bool TList<T>::empty()
{
	if (length == 0)
		return  false;
	if (length > 0)
		return  true;
}

template <typename T>
void TList<T>::push_back(T data)//ajoute une valeur en dernière position de la liste
{
	Node<T> *newItem = new Node<T>;//nouvelle node
	std::cout << "begin pushback ! new value at address " << *&newItem << std::endl;

	newItem->nodeVal = data;//je lui donne sa valeur
	std::cout << "previous value adress is " << Back()->prev << std::endl;

	newItem->prev = Back()->prev;//la node précédente est la node avant la fin
	//std::cout << "new prev is  " << newItem->prev << std::endl;

	Back()->prev->next = newItem;//je prends la place de cette nouvelle node
	Back()->prev = newItem;//je prends la place de cette nouvelle node
	newItem->next = Back();//je dis que ma node suivante est celle de fin


	length++;
}

template <typename T>
void TList<T>::insert(T data, int pos)
{
	Node<T>* tmp = Front();//nouvelle node

	for (int i = 0; i < length; ++i)
	{
		if (i == pos)//si on est à la bonne position pour ajouter
		{
			Node<T>* tmp_prev = tmp->prev;

			std::cout << "found i : " << i << " value allready in place is " << tmp->nodeVal << std::endl;
			std::cout << "before item "<< tmp_prev->nodeVal << std::endl;

			Node<T>* newItem = new Node<T>;//nouvelle node
			newItem->nodeVal = data;//je lui donne sa valeur
			newItem->prev = tmp->prev;//la node précédente est la node avant la fin
			newItem->next = tmp;//la node suivante est la node trouvée à la pos i
			tmp->prev = newItem;
			//std::cout << "tmp prev = " << tmp->prev->nodeVal << std::endl;
			tmp_prev->next = newItem;
			//std::cout << "tmp_prev next = " << tmp_prev->next->nodeVal << std::endl;
			length++;
			return;
		}

		tmp = tmp->next;
		
	}
}
