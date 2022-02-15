#include <iostream>
#include <vector>
#include <stack>
#include "../stack.hpp"
//#include "../vector.hpp"

int		main()
{
	std::vector<int> test;
	std::stack<char> test2;
	std::stack<char> test3;
	ft::stack<char> ftest2;
	ft::stack<char> ftest3;

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

	std::vector<int>::iterator it = test.begin();
	//std::vector<int>::iterator it(test.begin());

	std::cout << std::endl;
	std::cout << "it begin " << *it << std::endl;
	it = it + 1;
	std::cout << "it = it + 1 : " << *it << std::endl;
	std::cout << std::endl;

	char let = 'a';
	char let2 = 'a';
	char let3 = 'a';
	char let4 = 'a';

	test2.push(let);
	test2.push(let2);
	test3.push(let3);
	test3.push(let4);
	ftest2.push(let);
	ftest2.push(let2);
	ftest3.push(let3);
	ftest3.push(let4);

	bool te;
	te = (test2 == test3);
	std::cout << "test2 == test3 = " << te << std::endl;
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
	te = (ftest2 == ftest3);
	std::cout << std::endl;
	std::cout << "ftest2 == ftest3 = " << te << std::endl;
	te = (ftest2 != ftest3);
	std::cout << "ftest2 != ftest3 = " << te << std::endl;
	te = (ftest2 < ftest3);
	std::cout << "ftest2 < ftest3 = " << te << std::endl;
	te = (ftest2 > ftest3);
	std::cout << "ftest2 > ftest3 = " << te << std::endl;
	te = (ftest2 <= ftest3);
	std::cout << "ftest2 <= ftest3 = " << te << std::endl;
	te = (ftest2 >= ftest3);
	std::cout << "ftest2 >= ftest3 = " << te << std::endl;

	std::cout << std::endl;
	std::deque<char> const 					deck(3, 'z');
	ft::stack<char> 						copy(deck);
	std::stack<char> 						copy2(deck);
	std::cout << "copy.size() = " << copy.size() << std::endl;
	std::cout << "copy.empty() = " << copy.empty() << std::endl;
	std::cout << "copy.top() = " << copy.top() << std::endl;
	std::cout << "copy2.size() = " << copy2.size() << std::endl;
	std::cout << "copy2.empty() = " << copy2.empty() << std::endl;
	std::cout << "copy2.top() = " << copy2.top() << std::endl;
}
