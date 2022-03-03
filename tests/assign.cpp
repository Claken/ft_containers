// vector assign
#include <iostream>
#include <vector>
#include "../vector.hpp"

int main ()
{
	ft::vector<int> first(15, 1); //f t
	ft::vector<int>::iterator it = first.begin(); //f t

	*it = 666;

	ft::vector<int> second; // f t 
	std::vector<int> third;

	std::cout << "first :  ";
	for(unsigned int i = 0; i < first.capacity(); i++)
		std::cout << first[i] << ' ';
	std::cout << std::endl;

	first.assign (7,100);             // 7 ints with a value of 100

	std::cout << "first :  ";
	for(unsigned int i = 0; i < first.capacity(); i++)
		std::cout << first[i] << ' ';
	std::cout << std::endl;

	ft::vector<int>::iterator it1; //f t
	it1 = first.begin()+1;

	second.assign (it1,first.end()-1); // the 5 central values of first
	
	std::cout << "second : ";
	for(unsigned int i = 0; i < second.capacity(); i++)
		std::cout << second[i] << ' ';
	std::cout << std::endl;

	//int myints[] = {1776,7,4};
	//third.assign (myints,myints+3);   // assigning from array.

	std::cout << "Size of first: " << int (first.size()) << '\n';
	std::cout << "Size of second: " << int (second.size()) << '\n';
	//std::cout << "Size of third: " << int (third.size()) << '\n';

	return 0;
}
