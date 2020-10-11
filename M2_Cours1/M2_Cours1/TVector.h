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
    T& at(int pos);
    T& front();
    T& back();
    bool empty();// 0 check si il y a des valeurs ou pas
    void clear();//efface toutes les valeurs mais garde la capacité
    void print();
    void printAdresses();
	
    class iterator
    {
    private:
        T* ptr;
    	
    public:
        explicit iterator(T* p):ptr(p){};
        int operator*() const;
        iterator& operator++();
        iterator& operator++(int i);
        bool operator==(iterator& it);
        bool operator!=(iterator& it);

    };

    iterator begin();
    iterator end();
    iterator erase(iterator it);
    iterator erase(iterator it_first,iterator it_last);

};



