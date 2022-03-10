#pragma once

#include <iostream>
#include "utils.hpp"

namespace ft
{

	template<class Key, class T, class Pair = ft::pair<const Key, T>>
	class Node
	{
		public:

			Node					*parent;
			Node 					*right; 	// if the value is bigger or equal to the value of parent
			Node 					*left; 		// if the value is smaller than the value of parent
			Key						first;
			T						second;

			Node()
			{
				parent = NULL;
				right = NULL;
				left = NULL;
			}

			Node(Key key, T value)
			{
				parent = NULL;
				right = NULL;
				left = NULL;
				first = key;
				second = value;
			}
	};

	template<class Key, class T, class Pair = ft::pair<const Key, T>>
	class Tree
	{
		private:

		Node*	tree;
	};
}