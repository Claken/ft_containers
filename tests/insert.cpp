// inserting into a vector
#include <iostream>
#include <vector>
#include "../vector.hpp"

int main ()
{
	ft::vector<std::string> myvector (7, "100"); //f-t
	std::cout << "size = " << myvector.size() << std::endl;
	ft::vector<std::string>::iterator itb; //f-t
	itb = myvector.insert(myvector.begin()+4, "666");
	std::cout << "*itb = " << *itb << std::endl;

	std::cout << "size = " << myvector.size() << std::endl;
	myvector.reserve(20);
	ft::vector<std::string>::iterator it; //f-t
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
	myvector.insert (it+5,4,"300");
	std::cout << "capacity here : " << myvector.capacity() << std::endl;

	// "it" no longer valid, get a new one:
	it = myvector.begin();

	std::vector<std::string> anothervector (3,"400"); //f-t 
	myvector.insert (it+2, anothervector.begin(), anothervector.end());

	// 		int myarray [] = { 501,502,503 };
	//   myvector.insert (myvector.begin(), myarray, myarray+3);

	std::cout << "myvector contains:";
	for (it=myvector.begin(); it<myvector.end(); it++)
		std::cout << ' ' << *it;
	std::cout << '\n';

	return 0;
}