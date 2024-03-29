// swap maps
#include <iostream>
#include <map>
#include "../map.hpp"

#define TESTED_NS std

int main ()
{
	TESTED_NS::map<char,int> foo,bar;

	foo['x']=100;
	foo['y']=200;

	bar['a']=11;
	bar['b']=22;
	bar['c']=33;

	foo.swap(bar); // swap membre
	// swap(foo, bar); // swap non-membre

	std::cout << "foo contains:\n";
	for (TESTED_NS::map<char,int>::iterator it=foo.begin(); it!=foo.end(); ++it)
		std::cout << it->first << " => " << it->second << '\n';

	std::cout << "bar contains:\n";
	for (TESTED_NS::map<char,int>::iterator it=bar.begin(); it!=bar.end(); ++it)
		std::cout << it->first << " => " << it->second << '\n';

	return 0;
}
