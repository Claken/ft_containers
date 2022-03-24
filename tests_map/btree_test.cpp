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
    std::cout << "height == " << btree.getHeight(btree.tree()) << std::endl;

    btree.insert(ft::pair<TYPE1, int>("d", 12));

    std::cout << "first test =  " << btree.first() << std::endl;
    std::cout << "second test = " << btree.second() << std::endl;

	std::cout << PRINT << std::endl;
    btree.print2D(btree.tree(), 0);
    std::cout << "height == " << btree.getHeight(btree.tree()) << std::endl;

    std::cout << "tree empty ? " << btree.isTreeEmpty() << std::endl;

    btree.insert(ft::pair<TYPE1, int>("e", 24));

    std::cout << "first test =  " << btree.first() << std::endl;
    std::cout << "second test = " << btree.second() << std::endl;

	std::cout << PRINT << std::endl;
    btree.print2D(btree.tree(), 0);
    std::cout << "height == " << btree.getHeight(btree.tree()) << std::endl;


    btree.insert(ft::pair<TYPE1, int>("a", 100));

	std::cout << PRINT << std::endl;
    btree.print2D(btree.tree(), 0);
    std::cout << "height == " << btree.getHeight(btree.tree()) << std::endl;


    btree.insert(ft::pair<TYPE1, int>("b", 150));

    std::cout << PRINT << std::endl;
    btree.print2D(btree.tree(), 0);
    std::cout << "height == " << btree.getHeight(btree.tree()) << std::endl;


    btree.insert(ft::pair<TYPE1, int>("z", 100000));

    std::cout << PRINT << std::endl;
    btree.print2D(btree.tree(), 0);
    std::cout << "height  == " << btree.getHeight(btree.tree()) << std::endl;

    btree.insert(ft::pair<TYPE1, int>("y", 500000));

    std::cout << PRINT << std::endl;
    btree.print2D(btree.tree(), 0);
    std::cout << "height  == " << btree.getHeight(btree.tree()) << std::endl;

    
    btree.insert(ft::pair<TYPE1, int>("c", 585));

    std::cout << PRINT << std::endl;
    btree.print2D(btree.tree(), 0);

    btree.insert(ft::pair<TYPE1, int>("k", 3));
    std::cout << PRINT << std::endl;
    btree.print2D(btree.tree(), 0);

    btree.insert(ft::pair<TYPE1, int>("l", 85));
    std::cout << PRINT << std::endl;
    btree.print2D(btree.tree(), 0);

    btree.insert(ft::pair<TYPE1, int>("x", 78));
    std::cout << PRINT << std::endl;
    btree.print2D(btree.tree(), 0);

    std::cout << "SEGFAULT HERE" << std::endl;

    btree.insert(ft::pair<TYPE1, int>("f", 879));

    std::cout << PRINT << std::endl;
    btree.print2D(btree.tree(), 0);


    btree.insert(ft::pair<TYPE1, int>("g", 1));
    std::cout << PRINT << std::endl;
    btree.print2D(btree.tree(), 0);

    // std::cout << "delete 'x','g' et 'f'" << std::endl;
    // btree.calldeleteNode("x");
    // btree.calldeleteNode("g");
    // btree.calldeleteNode("f");
    // btree.calldeleteNode("x");
    // btree.calldeleteNode("e");
    // btree.calldeleteNode("a");
    // btree.calldeleteNode("l");
    // btree.calldeleteNode("b");
    // btree.calldeleteNode("c");
    // btree.calldeleteNode("z");
    // btree.calldeleteNode("d");
    // btree.calldeleteNode("k");
    // btree.calldeleteNode("y");

    std::cout << PRINT << std::endl;
    btree.print2D(btree.tree(), 0);

    std::cout << std::endl << "tree empty ? " << btree.isTreeEmpty() << std::endl;


    btree.callFindKeyInValue("i");
    btree.callFindKeyInValue("x");

    btree.printInorder(btree.tree());
    std::cout << std::endl;
    btree.printIndisorder(btree.tree());

    ft::Tree<TYPE1, int>::iterator it = btree.begin();

    std::cout << std::endl;
    for (it = btree.begin(); it != btree.end(); it++)
    {
        std::cout << "it->first == " << it->first << std::endl;
    }

    for (ft::Tree<TYPE1, int>::reverse_iterator it = btree.rbegin(); it != btree.rend(); it++)
    {
        std::cout << "reverse it->first == " << it->first << std::endl;
    }

    return (0);
}