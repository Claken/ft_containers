// vector assign
#include <iostream>
#include <vector>
#include "../vector.hpp"

int main ()
{
	ft::vector<int> first(15, 1);
	ft::vector<int>::iterator it = first.begin();

	*it = 666;

	std::vector<int> second;
	std::vector<int> third;

	for(int i = 0; i < first.capacity(); i++)
		std::cout << first[i] << ' ';
	std::cout << std::endl;
	first.assign (7,100);             // 7 ints with a value of 100
	for(int i = 0; i < first.capacity(); i++)
		std::cout << first[i] << ' ';
	std::cout << std::endl;

	// std::vector<int>::iterator it;
	// it=first.begin()+1;

	//second.assign (it,first.end()-1); // the 5 central values of first

	int myints[] = {1776,7,4};
	//third.assign (myints,myints+3);   // assigning from array.

	std::cout << "Size of first: " << int (first.size()) << '\n';
	//std::cout << "Size of second: " << int (second.size()) << '\n';
	//std::cout << "Size of third: " << int (third.size()) << '\n';

	return 0;
}
