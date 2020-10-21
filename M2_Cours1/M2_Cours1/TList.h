#pragma once

template <typename T> 
struct Node {
	T nodeVal; // la valeur de l'item ajouté à la liste
	Node<T>* next; // pointeur vers la node précédente
	Node<T>* prev; // pointeur vers la node suivante

public :
	//initialisation des valeurs. Value = T, et null pour les next / prev
	Node<T>()
	{
		next = nullptr;
		prev = nullptr;
		//std::cout << "new node created" << std::endl;
	}
};

template <typename T>
class TList
{
private:
	Node<T> head;//la première node de ma liste
	Node<T> tail;//la dernière node de ma liste
	size_t length = 0;

public:
	TList();//constructeur déclaré dans le cpp

	Node<T>* Front() { return head.next; }//fonction begin retourne la première vrai node de la liste
	Node<T>* Back() { return tail.prev; }//fonction begin retourne l'adresse de head = la fin du sandwich !
	int size();//retourne la taille de la liste
	bool empty();//retourne la taille de la liste
	void push_back(T data);//ajoute une valeur à la fin
	void insert(T data, int pos);

};



