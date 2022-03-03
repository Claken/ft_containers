#include <vector>
#include "../vector.hpp"
#include <iostream>

int main ()
{
	ft::vector<int> foo (3,2);
	ft::vector<int> bar (5,2);

	bar = foo;
	foo = ft::vector<int>();

	std::cout << "Size of foo: " << int(foo.size()) << '\n';
	std::cout << "Size of bar: " << int(bar.size()) << '\n';

	for (ft::vector<int>::iterator it = bar.begin(); it != bar.end(); it++)
	{
		std::cout << "bar : " << *it << '\n';
	}

	return 0;
}
