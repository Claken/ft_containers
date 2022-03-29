// assignment operator with maps
#include <iostream>
#include <map>
#include "../map.hpp"

#define TESTED_NS ft

int main ()
{
	TESTED_NS::map<char,int> first;
	TESTED_NS::map<char,int> second;

	first['x']=8;
	first['y']=16;
	first['z']=32;

	second=first;                // second now contains 3 ints
	first=TESTED_NS::map<char,int>();  // and first is now empty

	std::cout << "Size of first: " << first.size() << '\n';
	std::cout << "Size of second: " << second.size() << '\n';

	for (TESTED_NS::map<char,int>::iterator it = second.begin(); it != second.end(); ++it)
    {
		std::cout << it->first << " => " << it->second << '\n';
    }

	return 0;
}
