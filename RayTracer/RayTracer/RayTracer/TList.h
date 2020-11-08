#pragma once
#include <iostream>
#include <ostream>
#include <cassert>


template <typename T>
struct Node {
	T nodeVal; // la valeur de l'item ajout� � la liste
	Node<T>* next; // pointeur vers la node pr�c�dente
	Node<T>* prev; // pointeur vers la node suivante

public:
	//initialisation des valeurs. Value = T, et null pour les next / prev
	Node()
	{
		next = nullptr;
		prev = nullptr;
		//std::cout << "new node created" << std::endl;
	}

	~Node()
	{
		if(next)
		{
			delete next;
			next = nullptr;
		}if(prev)
		{
			delete prev;
			prev = nullptr;
		}
	}
};

template <typename T>
class TList
{
private:
	Node<T>* head;//la premi�re node de ma liste
	Node<T>* tail;//la derni�re node de ma liste
	size_t length = 0;


	friend std::ostream& operator<<(std::ostream& os, const TList<int>& list);//� faire en variante pour tous les type que l'on veut proposer

public:

	TList()
	{
		head = new Node<T>;//initialisation de la premi�re node
		tail = new Node<T>;//initialisation de la derni�re node

		length = 0;
		head->next = tail;//sera modifi�e apr�s la premi�re valeur ajout�e
		tail->prev = head;//idem pour la fin 
		//comme un sandwich !
		std::cout << "new list created " << std::endl;

	}

	Node<T>* Front() const { return head->next; }//fonction begin retourne la premi�re vrai node de la liste
	Node<T>* Back() const { return tail; }// retourne la derni�re node = la fin du sandwich !

	int Size()
	{
		return length;
	}

	bool Empty()
	{
		if (length == 0)
			return  false;
		if (length > 0)
			return  true;
	}

	void Push_back(const T& data)//ajoute une valeur en derni�re position de la liste
	{
		Node<T>* newItem = new Node<T>;//nouvelle node

		newItem->nodeVal = data;//je lui donne sa valeur
		std::cout << "begin pushback ! new value " << newItem->nodeVal << std::endl;

		newItem->prev = tail->prev;//la node pr�c�dente est la node avant la fin
		newItem->next = tail;//je dis que ma node suivante est celle de fin

		//std::cout << "head " << head << std::endl;
		//std::cout << "tail " << tail << std::endl;
		//std::cout << "tail-> prev " << tail->prev << std::endl;
		//std::cout << "newItem->prev " << newItem->prev << std::endl;
		//std::cout << "newItem->next " << newItem->next << std::endl;

		tail->prev->next = newItem;//je dis � la derni�re node avec value que je suis la nouvelle derni�re node
		tail->prev = newItem;//je prends la place de cette derni�re node

		length++;
	}

	void Insert(T data, int pos)
	{
		Node<T>* tmp = head->next;//nouvelle node

		assert(pos <= length && "INVALID POSITION");
		
		for (int i = 0; i < length; ++i)
		{
			if (i == pos)//si on est � la bonne position pour ajouter
			{
				Node<T>* tmp_prev = tmp->prev;

				std::cout << " value allready in place is " << tmp->nodeVal << std::endl;

				Node<T>* newItem = new Node<T>;//nouvelle node
				newItem->nodeVal = data;//je lui donne sa valeur
				newItem->prev = tmp->prev;//la node pr�c�dente est la node avant la fin
				newItem->next = tmp;//la node suivante est la node trouv�e � la pos i
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
};

std::ostream& operator<<(std::ostream& os, const TList<int>& list)
{

	os << "(";
	Node<int>* currentNode = list.head->next;
	for (int i = 0; i < list.length; ++i)
	{
		os << " " << currentNode->nodeVal;
		currentNode = currentNode->next;
	}
	return os << ")";
};



