#include "../btree.hpp"

#define PRINT "\n-------- PRINT2D --------"
#define TYPE1 std::string
#define TYPE2 int

int main(void)
{
    // ft::Tree<char, std::string> btree('a', "test");
    ft::Tree<TYPE1, int> btree;

    std::cout << "tree empty ? " << btree.isTreeEmpty() << std::endl;

    std::cout << "first test =  " << btree.first() << std::endl;
    std::cout << "second test = " << btree.second() << std::endl;

	std::cout << PRINT << std::endl;
    btree.print2D(btree.tree(), 0);
    std::cout << "height == " << btree.height(btree.tree()) << std::endl;

    btree.insert(ft::pair<TYPE1, int>("d", 12));

    std::cout << "first test =  " << btree.first() << std::endl;
    std::cout << "second test = " << btree.second() << std::endl;

	std::cout << PRINT << std::endl;
    btree.print2D(btree.tree(), 0);
    std::cout << "height == " << btree.height(btree.tree()) << std::endl;

    std::cout << "tree empty ? " << btree.isTreeEmpty() << std::endl;

    btree.insert(ft::pair<TYPE1, int>("e", 24));

    std::cout << "first test =  " << btree.first() << std::endl;
    std::cout << "second test = " << btree.second() << std::endl;

	std::cout << PRINT << std::endl;
    btree.print2D(btree.tree(), 0);
    std::cout << "height == " << btree.height(btree.tree()) << std::endl;


    btree.insert(ft::pair<TYPE1, int>("a", 100));

	std::cout << PRINT << std::endl;
    btree.print2D(btree.tree(), 0);
    std::cout << "height == " << btree.height(btree.tree()) << std::endl;


    btree.insert(ft::pair<TYPE1, int>("b", 150));

    std::cout << PRINT << std::endl;
    btree.print2D(btree.tree(), 0);
    std::cout << "height == " << btree.height(btree.tree()) << std::endl;


    btree.insert(ft::pair<TYPE1, int>("z", 100000));

    std::cout << PRINT << std::endl;
    btree.print2D(btree.tree(), 0);
    std::cout << "height  == " << btree.height(btree.tree()) << std::endl;

    btree.insert(ft::pair<TYPE1, int>("y", 500000));

    std::cout << PRINT << std::endl;
    btree.print2D(btree.tree(), 0);
    std::cout << "height  == " << btree.height(btree.tree()) << std::endl;

    btree.calldeleteNode("b");

    std::cout << PRINT << std::endl;
    btree.print2D(btree.tree(), 0);

    return (0);
}