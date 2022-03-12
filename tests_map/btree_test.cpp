#include "../btree.hpp"

#define PRINT "\n-------- PRINT2D --------" 

int main(void)
{
    // ft::Tree<char, std::string> btree('a', "test");
    ft::Tree<char, int> btree;


    std::cout << "first test =  " << btree.first() << std::endl;
    std::cout << "second test = " << btree.second() << std::endl;

	std::cout << PRINT << std::endl;
    btree.print2D(btree.tree(), 0);

    btree.insert(ft::pair<char, int>('d', 12));

    std::cout << "first test =  " << btree.first() << std::endl;
    std::cout << "second test = " << btree.second() << std::endl;

	std::cout << PRINT << std::endl;
    btree.print2D(btree.tree(), 0);

    btree.insert(ft::pair<char, int>('e', 24));

    std::cout << "first test =  " << btree.first() << std::endl;
    std::cout << "second test = " << btree.second() << std::endl;

	std::cout << PRINT << std::endl;
    btree.print2D(btree.tree(), 0);

    btree.insert(ft::pair<char, int>('a', 100));

	std::cout << PRINT << std::endl;
    btree.print2D(btree.tree(), 0);

    btree.insert(ft::pair<char, int>('b', 150));

    std::cout << PRINT << std::endl;
    btree.print2D(btree.tree(), 0);

    btree.insert(ft::pair<char, int>('z', 100000));

    std::cout << PRINT << std::endl;
    btree.print2D(btree.tree(), 0);

    return (0);
}