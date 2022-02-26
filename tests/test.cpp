#include <iostream>
#include <vector>
#include <stack>
#include "../stack.hpp"
#include "../vector.hpp"

int		main()
{
	std::vector<int> test;
	std::stack<int> test2;
	std::stack<int> test3;
	ft::stack<int> ftest2;
	ft::stack<int> ftest3;

	for (int i = 0; i < 20; i++)
	{
		std::cout << "size     : " << test.size() << std::endl;
		std::cout << "capacity : " << test.capacity() << std::endl;
		std::cout << "push_back" << std::endl;
		test.push_back(i * 2);
		std::cout << "size     : " << test.size() << std::endl;
		std::cout << "capacity : " << test.capacity() << std::endl;
		std::cout << i << std::endl << std::endl;
	}

	std::vector<int>::reverse_iterator rit = test.rbegin();
	std::vector<int>::reverse_iterator ritt = test.rend();

	std::cout << "rbegin : " << *rit << std::endl;
	std::cout << "rend :   " << *ritt << std::endl;

	/*
	test.clear();
	std::cout << "size     : " << test.size() << std::endl;
	std::cout << "capacity : " << test.capacity() << std::endl;
	std::vector<int>::iterator it = test.begin();
	for (int i = 0; i < test.capacity(); i++)
	{
		std::cout << "*it == " << *it << std::endl;
		it++;
	}
	*/

	test.reserve(100);
	std::cout << "new capacity : " << test.capacity() << std::endl;
	std::cout << "max_size : " << test.max_size() << std::endl;
	std::cout << "test[-1] == " << test[-1] << std::endl;
	std::cout << "test[21] == " << test[21] << std::endl;
	try
	{
		std::cout << "test.at(21) == " << test.at(21) << std::endl;
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}
	try
	{
		std::cout << "test.at(-5) == " << test.at(-5) << std::endl;
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}

	std::vector<int>::iterator it = test.begin();
	//std::vector<int>::iterator it(test.begin());
	ft::vector<int> testX(5, 2);
	try
	{
		std::cout << "test.at(21) == " << testX.at(21) << std::endl;
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}
	try
	{
		std::cout << "test.at(-5) == " << testX.at(-5) << std::endl;
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}
	std::vector<int> testouais(5, 2);
	std::cout << "testX[21] == " << testX[21] << std::endl;
	std::cout << "testX[-1] == " << testX[-1] << std::endl;
	std::cout << "testouais capacity = " << testouais.capacity() << std::endl;
	std::cout << "testX capacity     = " << testX.capacity() << std::endl;
	testX.reserve(100);
	std::cout << "capacity after testX.reserve(100) : " << testX.capacity() << std::endl;
	testX[0] = 5;
	testX[4] = 10;
	ft::vector<int>::iterator it2 = testX.begin();

	std::cout << "testX.front == " << testX.front() << std::endl;
	std::cout << "testX.back == " << testX.back() << std::endl;
	std::cout << "test.front == " << test.front() << std::endl;
	std::cout << "test.back == " << test.back() << std::endl;

	std::cout << std::endl;
	std::cout << "it begin " << *it2 << std::endl;
	it2 = it2 + 1;
	std::cout << "it = it + 1 : " << *it2 << std::endl;

	std::cout << "max_size testX: " << testX.max_size() << std::endl;
	std::cout << "max_size test:  " << test.max_size() << std::endl;
	std::cout << std::endl;


	ft::vector<int> twenty;
	for (int i = 0; i < 20; i++)
	{
		std::cout << "twenty size     : " << twenty.size() << std::endl;
		std::cout << "twenty capacity : " << twenty.capacity() << std::endl;
		std::cout << "twenty push_back" << std::endl;
		twenty.push_back(i * 2);
		std::cout << "twenty size     : " << twenty.size() << std::endl;
		std::cout << "twenty capacity : " << twenty.capacity() << std::endl;
		std::cout << "i == " << i << std::endl;
		std::cout << "twenty[] == " << twenty[i] << std::endl << std::endl;
	}

	ft::vector<int>::reverse_iterator ok = twenty.rbegin();
	ft::vector<int>::reverse_iterator tm = twenty.rend();

	std::cout << "rbegin : " << *ok << std::endl;
	std::cout << "rend :   " << *tm << std::endl;

	std::cout << std::endl;
	int let = 12;
	int let2 = 24;
	int let3 = 12;
	int let4 = 12;

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
	std::deque<int> const 					deck(3, 'z');
	ft::stack<int> 						copy(deck);
	std::stack<int> 						copy2(deck);
	std::cout << "copy.size() = " << copy.size() << std::endl;
	std::cout << "copy.empty() = " << copy.empty() << std::endl;
	std::cout << "copy.top() = " << copy.top() << std::endl;
	std::cout << "copy2.size() = " << copy2.size() << std::endl;
	std::cout << "copy2.empty() = " << copy2.empty() << std::endl;
	std::cout << "copy2.top() = " << copy2.top() << std::endl;
}
