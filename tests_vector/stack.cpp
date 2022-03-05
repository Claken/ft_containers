#include "../vector.hpp"
#include "../stack.hpp"
#include <vector>
#include <stack>
#include <iostream>
#include <string>
#include "stdlib.h"

#define TESTED_NAMESPACE	ft
#define TESTED_TYPE			std::string

int main()
{
	//ft::stack<float>			other_stack;
	TESTED_NAMESPACE::vector<TESTED_TYPE>		lst;
	//ft::vector<int>		lst;

	// lst.push_back(1);
	// lst.push_back(2);
	// lst.push_back(3);

	lst.push_back("salut");
	lst.push_back("tu vas bien?");
	lst.push_back("super");
	lst.push_back("et toi?");

	for (ft::vector<std::string>::iterator it = lst.begin(); it != lst.end(); it++)
	{
		std::cout << "lst = " << *it << std::endl;
	}

	

	//ft::stack<std::string, ft::vector<std::string> >	my_stack(lst);

	// std::cout << std::boolalpha << other_stack.empty() << std::endl;

	// other_stack.push(8.5); // 8.5;
	// other_stack.push(42.4242); // 8.5; 42.4242;
	// std::cout << other_stack.size() << '\n'; // 2

	// other_stack.pop(); // 8.5;
	// std::cout << other_stack.size() << '\n'; // 1

	// other_stack.push(78541.987); // 8.5; 78541.987;
	// std::cout << other_stack.size() << '\n'; // 2
	// std::cout << other_stack.top() << '\n'; //78541.987

	// std::cout << std::boolalpha << other_stack.empty() << std::endl;

	// const std::string const_top = my_stack.top();

	// std::cout << "const top: " << const_top << '\n';

	// while (!my_stack.empty())
	// {
	// 	std::cout << my_stack.top() << '\n';
	// 	my_stack.pop();
	// }

	return (0);
}
