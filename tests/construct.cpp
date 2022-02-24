// constructing vectors
#include <iostream>
#include <vector>
#include "../vector.hpp"

int main ()
{
	// constructors used in the same order as described above:
	//std::vector<int> first;                                // empty vector of ints
	ft::vector<int> second (4, 100);                       // four ints with value 100
    //std::cout << second.size() << std::endl;
	ft::vector<int> third (second.begin(), second.end());  // iterating through second
    std::cout << second.size() << std::endl;
    std::cout << second.capacity() << std::endl;
	ft::vector<int> fourth (third);                       // a copy of third

	// the iterator constructor can also be used to construct from arrays:
	int myints[] = {16,2,77,29};
	//ft::vector<int> fifth (myints, myints + sizeof(myints) / sizeof(int) );

	std::cout << "The contents of  ft third are:";
	for (ft::vector<int>::iterator it = third.begin(); it != third.end(); ++it)
		std::cout << ' ' << *it;
	std::cout << std::endl << "The contents of ft fourth are:";
    for (ft::vector<int>::iterator it = fourth.begin(); it != fourth.end(); ++it)
		std::cout << ' ' << *it;
	std::cout << '\n';

	return 0;
}