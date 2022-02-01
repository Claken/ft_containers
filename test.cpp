#include <iostream>
#include <vector>

int		main()
{
	std::vector<int> test;

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
}
