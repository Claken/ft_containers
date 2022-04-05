// constructing vectors
#include <iostream>
#include <vector>
#include "../vector.hpp"

#define TESTED_NAMESPACE	ft
#define TESTED_TYPE			int

int main ()
{
	// constructors used in the same order as described above:
	std::vector<int> first;                                // empty vector of ints
	TESTED_NAMESPACE::vector<TESTED_TYPE> second (4, 100);                       // four ints with value 100
	TESTED_NAMESPACE::vector<TESTED_TYPE> third (second.begin(), second.end());  // iterating through second
    std::cout << second.size() << std::endl;
    std::cout << second.capacity() << std::endl;
	TESTED_NAMESPACE::vector<TESTED_TYPE> fourth (third);                       // a copy of third

	// the iterator constructor can also be used to construct from arrays:
	int myints[] = {16,2,77,29};
	TESTED_NAMESPACE::vector<int> fifth (myints, myints + sizeof(myints) / sizeof(int) );

	std::cout << "The contents of third are:";
	for (TESTED_NAMESPACE::vector<TESTED_TYPE>::iterator it = third.begin(); it != third.end(); ++it)
		std::cout << ' ' << *it;
	std::cout << std::endl << "The contents of fourth are:";
    for (TESTED_NAMESPACE::vector<TESTED_TYPE>::iterator it = fourth.begin(); it != fourth.end(); ++it)
		std::cout << ' ' << *it;
	std::cout << std::endl << "The contents of fifth are:";
    for (TESTED_NAMESPACE::vector<TESTED_TYPE>::iterator it = fifth.begin(); it != fifth.end(); ++it)
		std::cout << ' ' << *it;
	std::cout << '\n';

	return 0;
}