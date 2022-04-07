// vector assign
#include <iostream>
#include <vector>
#include "../vector.hpp"

#define TESTED_NAMESPACE ft
#define TESTED_TYPE	std::string

int main ()
{
	TESTED_NAMESPACE::vector<TESTED_TYPE> first(15, "1"); //f t
	TESTED_NAMESPACE::vector<TESTED_TYPE>::iterator it = first.begin(); //f t

	*it = "666";

	TESTED_NAMESPACE::vector<TESTED_TYPE> second; // f t
	std::vector<int> third;

	std::cout << "first :  ";
	for(unsigned int i = 0; i < first.capacity(); i++)
		std::cout << first[i] << ' ';
	std::cout << std::endl;

	first.assign (7,"100");             // 7 ints with a value of 100

	std::cout << "first :  ";
	for(unsigned int i = 0; i < first.size(); i++)
		std::cout << first[i] << ' ';
	std::cout << std::endl;

	TESTED_NAMESPACE::vector<TESTED_TYPE>::iterator it1; //f t
	it1 = first.begin()+1;

	second.assign (it1,first.end()-1); // the 5 central values of first

	std::cout << "first capacity  : " << first.capacity() << std::endl;
	std::cout << "second capacity : " << second.capacity() << std::endl;
	std::cout << "second : ";
	for(unsigned int i = 0; i < second.size(); i++)
		std::cout << second[i] << ' ';
	std::cout << std::endl;

	//int myints[] = {1776,7,4};
	//third.assign (myints,myints+3);   // assigning from array.

	std::cout << "Size of first: " << int (first.size()) << '\n';
	std::cout << "Size of second: " << int (second.size()) << '\n';
	//std::cout << "Size of third: " << int (third.size()) << '\n';

	return 0;
}
