// vector::pop_back
#include <iostream>
#include <vector>
#include "../vector.hpp"

#define TESTED_NAMESPACE	ft
#define TESTED_TYPE			int

int main ()
{
	ft::vector<int> myvector;
	myvector.reserve(20);
	int sum (0);
	myvector.push_back (100);
	myvector.push_back (200);
	myvector.push_back (300);

	unsigned int i = 0;
	while (i < myvector.size())
	{
		std::cout << myvector[i++] << std::endl;
	}
	std::cout << myvector.capacity() << std::endl;

	while (!myvector.empty())
	{
		sum+=myvector.back();
		myvector.pop_back();
	}

	std::cout << "The elements of myvector add up to " << sum << '\n';

	return 0;
}