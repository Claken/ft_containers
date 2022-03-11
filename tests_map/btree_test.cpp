#include "../btree.hpp"

int main(void)
{
    // ft::Tree<std::string, std::string> btree("clé", "test");
    ft::Tree<std::string, int> btree;


    std::cout << "first test =  " << btree.first() << std::endl;
    std::cout << "second test = " << btree.second() << std::endl;



    return (0);
}