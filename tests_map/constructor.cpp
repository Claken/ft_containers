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

	std::cout << caca.max_size() << std::endl;
	std::cout << caca.size() << std::endl;

	std::cout << caca.get_allocator().max_size() << std::endl;

	if (caca > cici)
		std::cout << "equal" << std::endl;

	// caca['a']=10;
	// caca['b']=15;
	// caca['c']=20;
	// caca['d']=25;

	// for (std::map<char,int>::iterator it = caca.begin(); it != caca.end(); it++)
	// {
	// 	std::cout << "it->first  = " << it->first << std::endl;
	// 	std::cout << "it->second = " << it->second << std::endl;
	// 	std::cout << std::endl;
	// }

	//   std::map<char,int> second (first.begin(),first.end());

	//   std::map<char,int> third (second);

	//   std::map<char,int,classcomp> fourth;                 // class as Compare

	//   bool(*fn_pt)(char,char) = fncomp;
	//   std::map<char,int,bool(*)(char,char)> fifth (fn_pt); // function pointer as Compare

	return 0;
}
