#include <iostream>
#include <vector>
#include <stack>
#include "stack.hpp"

int		main()
{
	std::vector<int> test;
	ft::stack<char> test2;
	ft::stack<char> test3;

	for (int i = 0; i < 20; i++)
	{
		std::cout << "size     : " << test.size() << std::endl;
		std::cout << "capacity : " << test.capacity() << std::endl;
		std::cout << "push_back" << std::endl;
		test.push_back(i);
		std::cout << "size     : " << test.size() << std::endl;
		std::cout << "capacity : " << test.capacity() << std::endl;
		std::cout << i << std::endl << std::endl;
	}
	std::cout << "max_size : " << test.max_size() << std::endl;

	test2.push('z');
	test2.push('a');
	test3.push('a');
	test3.push('a');

	bool te;
	te = (test2 == test3);
	std::cout << "test2 == test3 = " << te << std::endl;
	/*
	te = (test2 != test3);
	std::cout << "test2 != test3 = " << te << std::endl;
	te = (test2 < test3);
	std::cout << "test2 < test3 = " << te << std::endl;
	te = (test2 > test3);
	std::cout << "test2 > test3 = " << te << std::endl;
	te = (test2 <= test3);
	std::cout << "test2 <= test3 = " << te << std::endl;
	te = (test2 >= test3);
	std::cout << "test2 >= test3 = " << te << std::endl;
	*/
}
