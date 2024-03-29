#include "../btree.hpp"
#include "../functional.hpp"

#define PRINT "\n-------- PRINT2D --------"
#define TYPE1 std::string
#define TYPE2 int

#define TYPE ft::pair<TYPE1, TYPE2>

int main(void)
{
    // ft::Tree<char, std::string> btree('a', "test");
    ft::Tree<TYPE, TYPE1, ft::_select_first<TYPE> > btree;

    std::cout << "tree empty ? " << btree.isTreeEmpty() << std::endl;

    std::cout << "first test =  " << btree.first() << std::endl;
    std::cout << "second test = " << btree.second() << std::endl;

	std::cout << PRINT << std::endl;
    btree.print2D(btree.tree(), 0);
    std::cout << "height == " << btree.getHeight(btree.tree()) << std::endl;

    btree.insert(ft::pair<TYPE1, TYPE2>("d", 12));

    std::cout << "first test =  " << btree.first() << std::endl;
    std::cout << "second test = " << btree.second() << std::endl;

	std::cout << PRINT << std::endl;
    btree.print2D(btree.tree(), 0);
    std::cout << "height == " << btree.getHeight(btree.tree()) << std::endl;

    std::cout << "tree empty ? " << btree.isTreeEmpty() << std::endl;

    btree.insert(ft::pair<TYPE1, TYPE2>("e", 24));

    std::cout << "first test =  " << btree.first() << std::endl;
    std::cout << "second test = " << btree.second() << std::endl;

	std::cout << PRINT << std::endl;
    btree.print2D(btree.tree(), 0);
    std::cout << "height == " << btree.getHeight(btree.tree()) << std::endl;


    btree.insert(ft::pair<TYPE1, TYPE2>("a", 100));

	std::cout << PRINT << std::endl;
    btree.print2D(btree.tree(), 0);
    // std::cout << "height == " << btree.getHeight(btree.tree()) << std::endl;


    btree.insert(ft::pair<TYPE1, TYPE2>("b", 150));

    std::cout << PRINT << std::endl;
    btree.print2D(btree.tree(), 0);
    std::cout << "height == " << btree.getHeight(btree.tree()) << std::endl;

    btree.insert(ft::pair<TYPE1, TYPE2>("z", 100000));

    std::cout << PRINT << std::endl;
    btree.print2D(btree.tree(), 0);
    // std::cout << "height  == " << btree.getHeight(btree.tree()) << std::endl;

    btree.insert(ft::pair<TYPE1, TYPE2>("y", 500000));

    std::cout << PRINT << std::endl;
    btree.print2D(btree.tree(), 0);
    // std::cout << "height  == " << btree.getHeight(btree.tree()) << std::endl;

    
    btree.insert(ft::pair<TYPE1, TYPE2>("c", 585));

    std::cout << PRINT << std::endl;
    btree.print2D(btree.tree(), 0);
    // std::cout << "height  == " << btree.getHeight(btree.tree()) << std::endl;

    btree.insert(ft::pair<TYPE1, TYPE2>("k", 3));
    std::cout << PRINT << std::endl;
    btree.print2D(btree.tree(), 0);
    // std::cout << "height  == " << btree.getHeight(btree.tree()) << std::endl;

    btree.insert(ft::pair<TYPE1, TYPE2>("l", 85));
    std::cout << PRINT << std::endl;
    btree.print2D(btree.tree(), 0);
    std::cout << "height  == " << btree.getHeight(btree.tree()) << std::endl;

    btree.insert(ft::pair<TYPE1, TYPE2>("x", 78));
    std::cout << PRINT << std::endl;
    btree.print2D(btree.tree(), 0);
    std::cout << "height  == " << btree.getHeight(btree.tree()) << std::endl;

    btree.insert(ft::pair<TYPE1, TYPE2>("f", 879));
    std::cout << PRINT << std::endl;
    btree.print2D(btree.tree(), 0);
    // std::cout << "height  == " << btree.getHeight(btree.tree()) << std::endl;

    btree.insert(ft::pair<TYPE1, TYPE2>("g", 1));
    std::cout << PRINT << std::endl;
    btree.print2D(btree.tree(), 0);

    std::cout << "delete nodes" << std::endl;
    btree.calldeleteNode("x");
    // btree.calldeleteNode("g");
    btree.calldeleteNode("f");
    btree.calldeleteNode("e");
    // btree.calldeleteNode("a");
    btree.calldeleteNode("l");
    btree.calldeleteNode("b");
    // btree.calldeleteNode("c");
    btree.calldeleteNode("z");
    btree.calldeleteNode("d");
    btree.calldeleteNode("k");
    btree.calldeleteNode("y");

    std::cout << std::endl << "tree empty ? " << btree.isTreeEmpty() << std::endl;

    // btree.insert(ft::pair<TYPE1, TYPE2>("ANOTHER ONE", 11));

    std::cout << PRINT << std::endl;
    btree.print2D(btree.tree(), 0);

    btree.callFindKeyInValue("i");
    btree.callFindKeyInValue("x");

    std::cout << "printInorder : ";
    btree.printInorder(btree.tree());
    std::cout << std::endl;

    std::cout << "iterator     : ";
    ft::Tree<TYPE, TYPE1, ft::_select_first<TYPE> >::iterator it;
    for (it = btree.begin(); it != btree.end(); ++it)
    {
        std::cout << it->first << " ";
    }
    std::cout << std::endl;

    if (it.base()->parent)
    	it--;
    std::cout << "(--it)->first == " << it->first << std::endl;

    std::cout << "reverse_iterator : ";
    for (ft::Tree<TYPE, TYPE1, ft::_select_first<TYPE> >::reverse_iterator it = btree.rbegin(); it != btree.rend(); it++)
    {
        std::cout << it->first << " ";
    }
    std::cout << std::endl;
    std::cout << "printIndisorder  : ";
    btree.printIndisorder(btree.tree());
    std::cout << std::endl;

    std::cout << "node max size == " << btree.get_allocator_node().max_size() << std::endl;
    std::cout << "type max size == " << btree.get_allocator_type().max_size() << std::endl;

    ft::Tree<TYPE, TYPE1, ft::_select_first<TYPE> > test = btree;

    for (ft::Tree<TYPE, TYPE1, ft::_select_first<TYPE> >::iterator it = test.begin(); it != test.end(); ++it)
    {
        std::cout << it->first << " ";
    }
    std::cout << std::endl;

    return (0);
}