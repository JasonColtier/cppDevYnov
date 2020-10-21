#pragma once

template <typename T>
class TVector
{
private:
    T* array; //le tableau de mes valeurs de type T
    int length = 0; //le nombre de valeurs dans mon array
    int capacity = 0; //la taille du tableau
    
public:
    TVector();//constructeur
    void push_back(T);//ajout d'une valeur à la fin
    void insert(T,int pos);//ajout d'une valeur à la fin
    int size();//combien de valeurs dans mon tableau ?
    T& operator[](int pos);//coppe cette valeur à index i
    T& at(int pos);//retourne l'adresse à la position pos
    T& front(); //retourne l'adresse de la première variable du vector
    T& back(); // dernière variable du vecteur
    bool empty();// 0 check si il y a des valeurs ou pas
    void clear();//efface toutes les valeurs mais garde la capacité
    void print(); // affiche toutes les variables
    void printAdresses(); // affiche les adresses en mémoire
	
    class iterator // un iterator permet de parcourir le vector
    {
    private:
        T* ptr;// un  iterator est composé d'un pointeur pointant vers l'adresse d'une des variable du vecteur
    	
    public:
        iterator(T* item):ptr(item){ std::cout << "iterator created ! pointing to :"<<*item<<std::endl; }// constructeur de l'itérateur initialisant son pointeur sur l'adresse de la variable du vector
        T & operator*();//l'opérateur * pour obtenir la valeur à l'adresse du pointeur en déréférençant
        iterator & operator++();
        iterator & operator++(int i);
        bool operator==(iterator& it);
        bool operator!=(iterator& it);
		iterator operator+(int add);
		iterator operator-(int sub);

    };

    iterator begin();
    iterator end();
    iterator erase(iterator it);
    iterator erase(iterator it_first,iterator it_last);

};



