#pragma once

#include <iostream>
#include "utils.hpp"

namespace ft
{

	template <class Key, class T, class Compare = std::less<Key>,
	class Allocator = std::allocator<ft::pair<const Key, T> > >
	class Node
	{
		public:

			Node					*parent;
			Node 					*right; 	// if the value is bigger or equal to the value of parent
			Node 					*left; 		// if the value is smaller than the value of parent
			Key						first;
			T						second;

			Node(const Allocator& = Allocator())
			{
				parent = NULL;
				right = NULL;
				left = NULL;
				Allocator().construct(first, Key());
				Allocator().construct(second, T());
			}

			Node(Key key, T value)
			{
				parent = NULL;
				right = NULL;
				left = NULL;
				Allocator().construct(first, key);
				Allocator().construct(second, value);
			}

			~Node()
			{
				Allocator().destroy(first, key);
				Allocator().destroy(second, value);
			}
	};

	template <class Key, class T, class Compare = std::less<Key>,
	class Allocator = std::allocator<ft::pair<const Key, T> > >
	class Tree
	{
		private:
		
			Node*		_tree;
			Allocator	_allocator_type;

		public:

			Tree(const Allocator& = Allocator())
			{
				this->_allocator_type = Allocator();
				this->_tree = this->_allocator_type.allocate(1);
			}
	};
}