#include <vector>
#include "../vector.hpp"
#include <iostream>

#define TESTED_NAMESPACE	ft
#define TESTED_TYPE			int

int main ()
{
	TESTED_NAMESPACE::vector<TESTED_TYPE> foo (3,2);
	TESTED_NAMESPACE::vector<TESTED_TYPE> bar (5,2);

	bar = foo;
	foo = TESTED_NAMESPACE::vector<TESTED_TYPE>();

	std::cout << "Size of foo: " << int(foo.size()) << '\n';
	std::cout << "Size of bar: " << int(bar.size()) << '\n';

	TESTED_NAMESPACE::vector<TESTED_TYPE>::const_reverse_iterator rit = bar.rbegin();
	for (TESTED_NAMESPACE::vector<TESTED_TYPE>::reverse_iterator it = bar.rbegin(); it != bar.rend(); it++)
	{
		std::cout << "bar : " << *it << '\n';
		if (it == rit)
			std::cout << "oui" << std::endl;	
	}

	return 0;
}
