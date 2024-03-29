// constructing maps
#include <iostream>
#include <map>
#include "../map.hpp"

bool fncomp (char lhs, char rhs) {return lhs<rhs;}

struct classcomp {
	bool operator() (const char& lhs, const char& rhs) const
	{return lhs<rhs;}
};

#define TESTED_NAMESPACE ft

int main ()
{
	TESTED_NAMESPACE::map<char,int> caca;
	TESTED_NAMESPACE::map<char,int> cici;

	std::cout << "max size == " << caca.max_size() << std::endl;
	std::cout << "size" << caca.size() << std::endl;

	std::cout << "get_allocator max size == " << caca.get_allocator().max_size() << std::endl;

	if (caca == cici)
		std::cout << "equal" << std::endl;

	caca['a']=10;
	caca['b']=15;
	caca['c']=20;
	caca['d']=25;
	caca['d']=7;

	caca.insert(TESTED_NAMESPACE::pair<char, int>('e', 789));

	std::cout << "CACA" << std::endl;
	for (TESTED_NAMESPACE::map<char,int>::iterator it = caca.begin(); it != caca.end(); it++)
	{
		std::cout << "it->first  = " << it->first << std::endl;
		std::cout << "it->second = " << it->second << std::endl;
		std::cout << std::endl;
	}
	std::cout << caca.size() << std::endl;

	TESTED_NAMESPACE::map<char,int> second (caca.begin(),caca.end());

	std::cout << "SECOND" << std::endl;
	for (TESTED_NAMESPACE::map<char,int>::iterator it = second.begin(); it != second.end(); it++)
	{
		std::cout << "it->first  = " << it->first << std::endl;
		std::cout << "it->second = " << it->second << std::endl;
		std::cout << std::endl;
	}
	std::cout << std::endl;

	TESTED_NAMESPACE::map<char,int> third (second);

	std::cout << "THIRD" << std::endl;
	for (TESTED_NAMESPACE::map<char,int>::iterator it = third.begin(); it != third.end(); it++)
	{
		std::cout << "it->first  = " << it->first << std::endl;
		std::cout << "it->second = " << it->second << std::endl;
		std::cout << std::endl;
	}
	std::cout << std::endl;

	TESTED_NAMESPACE::map<char,int,classcomp> fourth;                 // class as Compare
	fourth.insert(third.begin(), third.end());

	std::cout << "FOURTH" << std::endl;
	for (TESTED_NAMESPACE::map<char,int,classcomp>::iterator it = fourth.begin(); it != fourth.end(); it++)
	{
		std::cout << "it->first  = " << it->first << std::endl;
		std::cout << "it->second = " << it->second << std::endl;
		std::cout << std::endl;
	}
	std::cout << std::endl;

	// bool(*fn_pt)(char,char) = fncomp;
	// TESTED_NAMESPACE::map<char,int,bool(*)(char,char)> fifth (fn_pt); // function pointer as Compare
	// fifth.insert(third.begin(), third.end());

	// std::cout << "FIFTH" << std::endl;
	// for (TESTED_NAMESPACE::map<char,int,bool(*)(char,char)>::iterator it = fifth.begin(); it != fifth.end(); it++)
	// {
	// 	std::cout << "it->first  = " << it->first << std::endl;
	// 	std::cout << "it->second = " << it->second << std::endl;
	// 	std::cout << std::endl;
	// }

	return 0;
}
