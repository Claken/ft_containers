#pragma once

#include <iostream>
#include "utils.hpp"

#define SPACE 10

namespace ft
{

	template <class Key, class T, class Compare = std::less<Key>,
	class Allocator = std::allocator<ft::pair<const Key, T> > >
	class Node
	{
		public:

			Node							*parent;
			Node 							*right; 	// if the value is bigger or equal to the value of parent
			Node 							*left; 		// if the value is smaller than the value of parent
			ft::pair<const Key, T>			pair;
			Allocator						allocator;

			Node(const Allocator& = Allocator())
			{
				allocator = Allocator();
				allocator.construct(&pair, ft::make_pair(Key(), T()));
				parent = NULL;
				right = NULL;
				left = NULL;
			}

			Node(Key key, T value, const Allocator& = Allocator())
			{
				allocator = Allocator();
				allocator.construct(&pair, ft::make_pair(key, value));
				parent = NULL;
				right = NULL;
				left = NULL;
			}

			~Node()
			{
				allocator.destroy(&pair);
			}

	};

	template <class Key, class T, class Compare = std::less<Key>, class Allocator = std::allocator<ft::pair<const Key, T> >, class Allocator2 = std::allocator<Node<Key, T> > >
	class Tree
	{

		public:
		
			typedef ft::pair<const Key, T> 						value_type;
			typedef Node<Key, T>*								node;

			Tree(const Allocator& = Allocator(), const Allocator2& = Allocator2())
			{
				this->_allocator_type = Allocator();
				this->_allocator_node = Allocator2();
				this->_tree = this->_allocator_node.allocate(1);
				this->_allocator_node.construct(this->_tree, Node<Key, T>());
			}

			Tree(Key key, T value, const Allocator& = Allocator(), const Allocator2& = Allocator2())
			{
				this->_allocator_type = Allocator();
				this->_allocator_node = Allocator2();
				this->_tree = this->_allocator_node.allocate(1);
				this->_allocator_node.construct(this->_tree, Node<Key, T>(key, value));
			}

			~Tree()
			{
				this->_allocator_node.destroy(this->_tree);
				this->_allocator_node.deallocate(this->_tree, 1);
			}

			typename ft::pair<const Key, T>::first_type first()
			{
				return (this->_tree->pair.first);
			}

			typename ft::pair<const Key, T>::second_type second()
			{
				return (this->_tree->pair.second);
			}

			// void insert(const value_type& x)
			// {

			// }

			node tree()
			{
				return (this->_tree);
			}

			void print2D(node r, int space)
			{
				if (r == NULL) // Base case  1
					return;
				space += SPACE; // Increase distance between levels   2
				print2D(r->right, space); // Process right child first 3 
				std::cout << std::endl;
				for (int i = SPACE; i < space; i++) // 5 
					std::cout << " "; // 5.1  
				std::cout << r->pair.first << "\n"; // 6
				std::cout << r->pair.second << "\n"; // 6
				print2D(r->left, space); // Process left child  7
			}

//   void printPreorder(TreeNode * r) //(current node, Left, Right) 
//   {
//     if (r == NULL)
//       return;
//     /* first print data of node */
//     cout << r -> value << " ";
//     /* then recur on left sutree */
//     printPreorder(r -> left);
//     /* now recur on right subtree */
//     printPreorder(r -> right);
//   }
		
		private:
		
			node				_tree;
			Allocator			_allocator_type;
			Allocator2			_allocator_node;

	};
}