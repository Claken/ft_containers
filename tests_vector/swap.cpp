// swap vectors
#include <iostream>
#include <vector>
#include "../vector.hpp"

#define TESTED_NAMESPACE	ft
#define TESTED_TYPE			int

// int main (void)
// {
// 	TESTED_NAMESPACE::vector<TESTED_TYPE> foo (5,100);   // three ints with a value of 100
// 	TESTED_NAMESPACE::vector<TESTED_TYPE> bar (3,200);   // five ints with a value of 200

// 	foo.swap(bar);

// 	std::cout << "foo contains:";
// 	for (unsigned i=0; i<foo.size(); i++)
// 		std::cout << ' ' << foo[i];
// 	std::cout << '\n';

// 	std::cout << "bar contains:";
// 	for (unsigned i=0; i<bar.size(); i++)
// 		std::cout << ' ' << bar[i];
// 	std::cout << '\n';

// 	return 0;
// }

//swap (vector overload)

int main (void)
{
	//unsigned int i;
	TESTED_NAMESPACE::vector<TESTED_TYPE> foo (3,100);   // three ints with a value of 100
	TESTED_NAMESPACE::vector<TESTED_TYPE> bar (5,200);   // five ints with a value of 200

	// foo.swap(bar); // swap membre
	swap(foo, bar); // swap non-membre

	std::cout << "foo contains:";
	for (TESTED_NAMESPACE::vector<TESTED_TYPE>::iterator it = foo.begin(); it!=foo.end(); ++it)
		std::cout << ' ' << *it;
	std::cout << '\n';

	std::cout << "bar contains:";
	for (TESTED_NAMESPACE::vector<TESTED_TYPE>::iterator it = bar.begin(); it!=bar.end(); ++it)
		std::cout << ' ' << *it;
	std::cout << '\n';

	return 0;
}