#include <ostream>

#include "AbstractHero.h"
#include "AwsomeHero.h"
#include "BasicCustomHero.h"
#include "Hero.h"
#include "TVector.h"
#include "TVector.cpp"
#include "TList.h"
#include "TList.cpp"
#include "vector"

int main()//entrée du programme, juste à nommer le fichier main.cpp avec un int / void main()
{
	AbstractHero* pHero = new Hero();//j'instancie un nouveau héro avec un pointeur de type AbstractHero
	pHero->Action(); //j'appelle la fonction Action() de mon héro

	AwsomeHero* p_awsome_hero = new AwsomeHero();
	p_awsome_hero->Action();

	//BasicCustomHero* basic_custom_hero = new BasicCustomHero();

	//TVECTOR
	std::vector<char> standardVector;
	TVector<int> myVector;

	myVector.push_back(1);
	myVector.push_back(2);

	std::cout << myVector[0] <<std::endl;
	std::cout << myVector[1] <<std::endl;

	std::cout << "Size is : "<<myVector.size() << std::endl;
	std::cout << "is empty ? " << myVector.empty()<< std::endl;
	std::cout << "clearing array "<< std::endl;
	myVector.clear();
	std::cout << "is empty ? " << myVector.empty() << std::endl;
	myVector.push_back(4);
	myVector.push_back(5);
	myVector.push_back(6);
	myVector.push_back(7);
	myVector.push_back(8);

	
	std::cout << "at 2 : "<<myVector.at(2) << std::endl;
	std::cout << "at 2 : "<<myVector.at(2) << std::endl;
	std::cout << "front " << myVector.front() << std::endl;
	std::cout << "back " << myVector.back() << std::endl;

	myVector.print();
	myVector.insert(100, 3);
	myVector.print();
	 
	std::cout<< "begin " << *myVector.begin() << std::endl;
	std::cout << "end " << *myVector.end() << std::endl;

	myVector.printAdresses();
	
	std::cout << " erase at [2] " << *myVector.erase(myVector.begin()+2) << std::endl;
	 
	myVector.print();   

	
	//LIST
	TList<char> myList;  
	
	myList.push_back('a');
	myList.push_back('b');          
	myList.push_back('c');

	std::cout << "first value : " << myList.Front()->nodeVal << std::endl;
	std::cout << "end value : " << myList.Back()->prev->nodeVal << std::endl;
	std::cout << "second value : " << myList.Front()->next->nodeVal << std::endl;

	std::cout << "list size : " << myList.size() << std::endl;

	myList.insert('u', 1);
	std::cout << "first value : " << myList.Front()->nodeVal << std::endl;    
	std::cout << "second value : " << myList.Front()->next->nodeVal << std::endl;
	std::cout << "third value : " << myList.Front()->next->next->nodeVal << std::endl;

	std::cout << "is empty ? "<<myList.empty()<<std::endl;
	    
	std::cout << "end"<<std::endl;
	
	
}