// inserting into a vector
#include <iostream>
#include <vector>
#include "../vector.hpp"

#define TESTED_NAMESPACE	std
#define TESTED_TYPE			std::string

int main ()
{
	TESTED_NAMESPACE::vector<TESTED_TYPE> myvector (7, "100"); //f-t
	std::cout << "size = " << myvector.size() << std::endl;
	TESTED_NAMESPACE::vector<TESTED_TYPE>::iterator itb; //f-t
	itb = myvector.insert(myvector.begin()+4, "666");
	std::cout << "*itb = " << *itb << std::endl;

	std::cout << "size = " << myvector.size() << std::endl;
	// myvector.reserve(20);
	TESTED_NAMESPACE::vector<TESTED_TYPE>::iterator it; //f-t
	std::cout << "capacity : " << myvector.capacity() << std::endl;

	it = myvector.begin();
	std::cout << "*it = " << *it << std::endl;
	std::cout << "*myvector.begin() = " << *(myvector.begin()) << std::endl;
	// ++it;
	// *it = 150;
	// ++it;
	// *it = 200

	it = myvector.insert ( it , "200" );
	it = myvector.begin();
	std::cout << *(it + 3) << std::endl;
	std::cout << *(myvector.end() - 1) << std::endl;

	myvector.insert (it+5,4,"300");
	std::cout << "capacity here : " << myvector.capacity() << std::endl;

	// "it" no longer valid, get a new one:
	it = myvector.begin();

	std::vector<TESTED_TYPE> anothervector (3,"400"); //f-t 
	myvector.insert (it+2, anothervector.begin(), anothervector.end());

	std::cout << "myvector contains:";
	for (it=myvector.begin(); it<myvector.end(); it++)
		std::cout << ' ' << *it;
	std::cout << '\n';

	return 0;
}