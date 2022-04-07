// resizing vector
#include <iostream>
#include <vector>
#include "../vector.hpp"

#define TESTED_NAMESPACE ft
#define TESTED_TYPE	int

int main ()
{
	TESTED_NAMESPACE::vector<int> myvector;

	//set some initial content:
	for (int i = 1; i < 10; i++)
    	myvector.push_back(i);

	myvector.resize(5);
	myvector.resize(8,100);
	myvector.resize(12);

	std::cout << "myvector contains:";
	for (unsigned int i=0;i<myvector.size();i++)
		std::cout << ' ' << myvector[i];
	std::cout << '\n';

	return 0;
}

// void	is_empty(TESTED_NAMESPACE::vector<TESTED_TYPE> const &vct)
// {
// 	std::cout << "is_empty: " << vct.empty() << std::endl;
// }

// int		main(void)
// {
// 	const int start_size = 7;
// 	TESTED_NAMESPACE::vector<TESTED_TYPE> vct(start_size, 20);
// 	TESTED_NAMESPACE::vector<TESTED_TYPE> vct2;
// 	TESTED_NAMESPACE::vector<TESTED_TYPE>::iterator it = vct.begin();

// 	for (int i = 2; i < start_size; ++i)
// 	{
// 		it[i] = (start_size - i) * 3;
// 		std::cout << *it << std::endl;
// 	}
// 	// printSize(vct, true);

// 	vct.resize(10, 42);
// 	// printSize(vct, true);

// 	vct.resize(18, 43);
// 	// printSize(vct, true);
// 	vct.resize(10);
// 	// printSize(vct, true);
// 	vct.resize(23, 44);
// 	// printSize(vct, true);
// 	vct.resize(5);
// 	// printSize(vct, true);
// 	vct.reserve(5);
// 	vct.reserve(3);
// 	// printSize(vct, true);
// 	vct.resize(87);
// 	vct.resize(5);
// 	// printSize(vct, true);

// 	is_empty(vct2);
// 	vct2 = vct;
// 	is_empty(vct2);
// 	vct.reserve(vct.capacity() + 1);
// 	// printSize(vct, true);
// 	// printSize(vct2, true);

// 	vct2.resize(0);
// 	is_empty(vct2);
// 	// printSize(vct2, true);
// 	return (0);
// }