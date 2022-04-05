// vector comparisons
#include <iostream>
#include <vector>
#include "../vector.hpp"

#define TESTED_NAMESPACE	ft
#define TESTED_TYPE			int

int main ()
{
	TESTED_NAMESPACE::vector<TESTED_TYPE> foo (3,100);   // three ints with a value of 100
	TESTED_NAMESPACE::vector<TESTED_TYPE> bar (2,200);   // two ints with a value of 200

	TESTED_NAMESPACE::vector<TESTED_TYPE>::iterator it = foo.begin();
	TESTED_NAMESPACE::vector<TESTED_TYPE>::const_iterator cit = foo.begin();

	if (it == cit)
		std::cout << "it et cit sont pareils" << std::endl;

	if (foo == bar)
		std::cout << "foo and bar are equal\n";
	if (foo != bar)
		std::cout << "foo and bar are not equal\n";
	if (foo < bar)
		std::cout << "foo is less than bar\n";
	if (foo > bar)
		std::cout << "foo is greater than bar\n";
	if (foo <= bar)
		std::cout << "foo is less than or equal to bar\n";
	if (foo >= bar)
		std::cout << "foo is greater than or equal to bar\n";

	return 0;
}