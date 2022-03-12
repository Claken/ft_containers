#include "../btree.hpp"

int main(void)
{
    ft::Tree<char, std::string> btree('a', "test");
    // ft::Tree<std::string, int> btree;


    std::cout << "first test =  " << btree.first() << std::endl;
    std::cout << "second test = " << btree.second() << std::endl;

    btree.print2D(btree.tree(), 0);


    return (0);
}