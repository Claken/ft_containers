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
			bool							full;
			Allocator						allocator;

			Node(const Allocator& = Allocator())
			{
				allocator = Allocator();
				allocator.construct(&pair, ft::make_pair(Key(), T()));
				parent = NULL;
				right = NULL;
				left = NULL;
				full = false;
			}

			Node(Key key, T value, const Allocator& = Allocator())
			{
				allocator = Allocator();
				allocator.construct(&pair, ft::make_pair(key, value));
				parent = NULL;
				right = NULL;
				left = NULL;
				full = false;
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
		
			typedef ft::pair<const Key, T> 			value_type;
			typedef Node<Key, T>					node;
			typedef node*							pointer;

			Tree(const Allocator& = Allocator(), const Allocator2& = Allocator2(), const Compare& comp = Compare())
			{
				this->_allocator_type = Allocator();
				this->_allocator_node = Allocator2();
				this->_compare = comp;
				this->_tree = this->_allocator_node.allocate(1);
				this->_allocator_node.construct(this->_tree, Node<Key, T>());
			}

			Tree(Key key, T value, const Allocator& = Allocator(), const Allocator2& = Allocator2(), const Compare& comp = Compare())
			{
				this->_allocator_type = Allocator();
				this->_allocator_node = Allocator2();
				this->_compare = comp;
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

			void insert(const value_type& x)
			{
				if (!this->_tree->full)
				{
					this->_allocator_type.destroy(&this->_tree->pair);
					this->_allocator_type.construct(&this->_tree->pair, ft::make_pair(x.first, x.second));
					this->_tree->full = true;
				}
				else
				{
					pointer newnode = this->_allocator_node.allocate(1);
					this->_allocator_node.construct(newnode, Node<Key, T>(x.first, x.second));
					newnode->full = true;

					pointer current = this->_tree;
					pointer svg;
					bool dir;

					while (current != NULL)
					{
						svg = current;
						if (this->_compare(x.first, current->pair.first))
						{
							current = current->left;
							dir = true;
						}
						else
						{
							current = current->right;
							dir = false;
						}
					}
					current = newnode;
					current->parent = svg;
					if (dir)
						current->parent->left = current;
					else
						current->parent->right = current;
					pointer unba = isUnbalanced(current);
					if (unba != NULL)
						std::cout << "unbalanced == " << unba->pair.first << std::endl;
				}
			}

			int height(pointer r)
			{
				if (r == NULL)
					return -1;
				int lheight = height(r->left);
				int rheight = height(r->right);
				if (lheight > rheight)
					return (lheight + 1);
				else
					return (rheight + 1);
			}

			int getBalanceFactor(pointer n)
			{
  				if (n == NULL)
     				return -1;
   				return abs(height(n->left) - height(n->right));
  			}

			pointer isUnbalanced(pointer curr)
			{
				while (curr != NULL)
				{
					if (getBalanceFactor(curr) > 1)
						return (curr);
					curr = curr->parent;
				}
				return NULL;
			}
			


			pointer tree()
			{
				return (this->_tree);
			}

			void print2D(pointer r, int space)
			{
				if (r == NULL)
					return;
				space += SPACE;
				print2D(r->right, space);
				std::cout << std::endl;
				for (int i = SPACE; i < space; i++)
					std::cout << " ";
				std::cout << r->pair.first << std::endl;
				for (int i = SPACE; i < space; i++)
					std::cout << " ";
				std::cout << r->pair.second << std::endl;
				if (r->parent != NULL)
				{
					for (int i = SPACE; i < space; i++)
						std::cout << " ";
					std::cout << "-" << std::endl;
					for (int i = SPACE; i < space; i++)
						std::cout << " ";
					std::cout << r->parent->pair.first << std::endl;
					for (int i = SPACE; i < space; i++)
						std::cout << " ";
					std::cout << r->parent->pair.second << std::endl;
				}
				print2D(r->left, space);
			}

//   void printPreorder(Treepointer  r) //(current node, Left, Right) 
//   {
//     if (r == NULL)
//       return;
//     /* first print data of pointer /
//     cout << r -> value << " ";
//     /* then recur on left sutree */
//     printPreorder(r -> left);
//     /* now recur on right subtree */
//     printPreorder(r -> right);
//   }
		
		private:
		
			pointer				_tree;
			Allocator			_allocator_type;
			Allocator2			_allocator_node;
			Compare				_compare;

	};
}