// erasing from vector
#include <iostream>
#include <vector>
#include "../vector.hpp"

int main ()
{
	std::vector<int> myvector;

	// set some values (from 1 to 10)
	for (int i=1; i<=10; i++)
		myvector.push_back(i);

	// erase the 6th element
	// std::vector<int>::iterator it = myvector.erase (myvector.begin()+5);

	// std::cout << "*it == " << *it << std::endl;

	// // erase the first 3 elements:
	std::vector<int>::iterator it2 = myvector.erase (myvector.begin(),myvector.end()-1);

	std::cout << "*it2 == " << *it2 << std::endl;

	std::cout << "myvector contains:";
	for (unsigned i=0; i<myvector.size(); ++i)
		std::cout << ' ' << myvector[i];
	std::cout << '\n';

	return 0;
}