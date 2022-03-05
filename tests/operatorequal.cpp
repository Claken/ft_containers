#include <vector>
#include "../vector.hpp"
#include <iostream>

int main ()
{
	std::vector<int> foo (3,2);
	std::vector<int> bar (5,2);

	bar = foo;
	foo = std::vector<int>();

	std::cout << "Size of foo: " << int(foo.size()) << '\n';
	std::cout << "Size of bar: " << int(bar.size()) << '\n';

	std::vector<int>::const_reverse_iterator rit = bar.rbegin();
	for (std::vector<int>::reverse_iterator it = bar.rbegin(); it != bar.rend(); it++)
	{
		std::cout << "bar : " << *it << '\n';
		if (it == rit)
			std::cout << "oui" << std::endl;	
	}

	return 0;
}
