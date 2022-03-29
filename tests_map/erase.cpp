// erasing from map
#include <iostream>
#include <map>
#include "../map.hpp"

#define TESTED_NS ft

int main ()
{
	TESTED_NS::map<char,int> mymap;

    std::cout << "empty ? " << mymap.empty() << std::endl;

	TESTED_NS::map<char,int>::iterator it;

	// insert some values:
	mymap['a']=10;
	mymap['b']=20;
	mymap['c']=30;
	mymap['d']=40;
	mymap['e']=50;


	mymap.insert(TESTED_NS::pair<char, int>('e', 789));
	std::cout << "count == " << mymap.count('e') << std::endl;

	for (TESTED_NS::map<char,int>::reverse_iterator it=mymap.rend(); it!=mymap.rbegin(); --it)
	{
		std::cout << it->first << " => " << it->second << '\n';
	}

	it=mymap.find('b');
	mymap.erase (it);                   // erasing by iterator

	std::cout << mymap.erase ('c') << std::endl;                  // erasing by key

	it=mymap.find ('a');
	mymap.erase ( it, mymap.end() );    // erasing by range

    std::cout << "empty ? " << mymap.empty() << std::endl;

    it = mymap.begin();

    std::cout << "it->first  == " << it->first << std::endl;
    std::cout << "it->second == " << it->second << std::endl;

	return 0;
}