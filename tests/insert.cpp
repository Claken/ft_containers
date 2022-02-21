// inserting into a vector
#include <iostream>
#include <vector>
#include "../vector.hpp"

int main ()
{
	ft::vector<int> myvector (7,100);
	ft::vector<int>::iterator itb;
	itb = myvector.begin();
	std::cout << "*itb = " << *itb << std::endl;


	myvector.reserve(20);
	ft::vector<int>::iterator it;
	std::cout << "capacity : " << myvector.capacity() << std::endl;

	it = myvector.begin();
	std::cout << "*it = " << *it << std::endl;
	std::cout << "*myvector.begin() = " << *(myvector.begin()) << std::endl;
	// ++it;
	// *it = 150;
	// ++it;
	// *it = 200;
	//it = myvector.insert ( it , 200 );
	// it = myvector.begin();
	// std::cout << *(it + 3) << std::endl;
	// std::cout << *(myvector.end() - 1) << std::endl;
	myvector.insert (it+3,3,300);
	std::cout << "capacity : " << myvector.capacity() << std::endl;

	// "it" no longer valid, get a new one:
	//   it = myvector.begin();

	//   std::vector<int> anothervector (2,400);
	//   myvector.insert (it+2,anothervector.begin(),anothervector.end());

	//   int myarray [] = { 501,502,503 };
	//   myvector.insert (myvector.begin(), myarray, myarray+3);

	std::cout << "myvector contains:";
	for (it=myvector.begin(); it<myvector.end(); it++)
		std::cout << ' ' << *it;
	std::cout << '\n';

	return 0;
}