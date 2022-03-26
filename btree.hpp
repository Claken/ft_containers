#pragma once

#include <iostream>
#include <cmath>
#include "utils.hpp"
#include "iterator.hpp"

#define SPACE 10

namespace ft
{

	template<class Node, class Value>
	class tree_iterator
	{
		public:
		typedef Value  								value_type;
      	typedef Value& 								reference;
      	typedef Value* 								pointer;
		typedef Node								node_type;
		typedef Node*								node_pointer;
		typedef std::ptrdiff_t						difference_type;
		typedef std::bidirectional_iterator_tag		iterator_category;

		node_pointer								current;
		node_pointer								root;

		tree_iterator() : current(NULL), root(NULL), _isRev(false), _isEnd(false) {}

		tree_iterator(node_pointer node, node_pointer tree, bool isRev = false, bool end = false)
		: current(node), root(tree), _isRev(isRev), _isEnd(end) {}

		tree_iterator(const tree_iterator& instance)
		{
			*this = instance;
		}

		~tree_iterator() {}

		tree_iterator& operator=(const tree_iterator& instance)
		{
			this->current = instance.current;
			this->root = instance.root;
			this->_isRev = instance._isRev;
			this->_isEnd = instance._isEnd;
			return *this;
		}

		reference operator*() const
		{
			return (this->current->pair);
		}

      	pointer operator->() const
		{
			return (&this->operator*());
		}
 
      	tree_iterator& operator++()
    	{
			this->current = this->increase();
			return *this;
      	}

      	tree_iterator operator++(int)
      	{
			tree_iterator tmp = *this;
			this->current = this->increase();
			return tmp;
	  	}

     	tree_iterator& operator--()
      	{
			this->current = this->decrease();
			return *this;
      	}
		
		tree_iterator operator--(int)
      	{
			tree_iterator tmp = *this;
			this->current = this->decrease();
			return tmp;
	  	}

		private:

		bool			_isRev;
		bool			_isEnd;

		node_pointer decrease()
		{
			node_pointer curr = this->root;
			int height = this->getHeight(curr);
			node_pointer nodes[height];
			int i = 0;
			if (this->_isRev && this->_isEnd)
			{
				this->_isEnd = false;
				return current;
			}
			while (curr != NULL && curr->pair.first != current->pair.first)
			{
				nodes[i++] = curr;
				if (this->current->compare(current->pair, curr->pair))
					curr = curr->left;
				else
					curr = curr->right;
			}
			i--;
			if (current->left == NULL)
			{
				while (i > -1 && this->current->compare(this->current->pair, nodes[i]->pair))
					i--;
				if (i > -1)
					return nodes[i];
			}
			else
			{
				return this->farRightNode(this->current->left);
			}
			return NULL;
		}

		node_pointer increase()
		{
			node_pointer curr = this->root;
			int height = this->getHeight(curr);
			node_pointer nodes[height];
			int i = 0;
			if (this->_isRev && (this->current == this->farRightNode(this->root) || this->current == this->farLeftNode(this->root)))
				this->_isEnd = true;
			while (curr != NULL && curr->pair.first != current->pair.first)
			{
				nodes[i++] = curr;
				if (this->current->compare(current->pair, curr->pair))
					curr = curr->left;
				else
					curr = curr->right;
			}
			i--;
			if (current->right == NULL)
			{
				while (i > -1 && this->current->compare(nodes[i]->pair, this->current->pair))
					i--;
				if (i > -1)
					return nodes[i];
			}
			else
			{
				return this->farLeftNode(this->current->right);
			}
			return NULL;
		}

		node_pointer farLeftNode(node_pointer curr)
		{
			node_pointer current = curr;
			while (current->left != NULL)
				current = current->left;
			return (current);
		}

		node_pointer farRightNode(node_pointer curr)
		{
			node_pointer current = curr;
			while (current->right != NULL)
				current = current->right;
			return (current);
		}

		int getHeight(node_pointer r)
		{
			if (r == NULL)
				return -1;
			int lheight = getHeight(r->left);
			int rheight = getHeight(r->right);
			if (lheight > rheight)
				return (lheight + 1);
			else
				return (rheight + 1);
		}
  };

 	template<class Tx, class Ux, class Ty, class Uy>
	bool	operator==(const tree_iterator<Tx, Ux>& x, const tree_iterator<Ty, Uy>& y)
	{
		return (x.current == y.current);
	}

	template<class Tx, class Ux, class Ty, class Uy>
	bool	operator!=(const tree_iterator<Tx, Ux>& x, const tree_iterator<Ty, Uy>& y)
	{
		return (x.current != y.current);
	}

	template <class Pair, class Key, class Compare = std::less<Key>, class Allocator = std::allocator<Pair> >
	class Node
	{
		public:

			// Node							*parent;
			Node 							*right; 	// if the value is bigger or equal to the value of parent
			Node 							*left; 		// if the value is smaller than the value of parent
			Pair							pair;
			bool							full;
			Allocator						allocator;
			Compare							compare;

			Node(const Allocator& = Allocator(), const Compare& = Compare())
			{
				allocator = Allocator();
				compare = Compare();
				allocator.construct(&pair, ft::make_pair(pair.first, pair.second));
				// parent = NULL;
				right = NULL;
				left = NULL;
				full = false;
			}

			Node(Pair value, const Allocator& = Allocator())
			{
				allocator = Allocator();
				compare = Compare();
				allocator.construct(&pair, ft::make_pair(value.first, value.second));
				// parent = NULL;
				right = NULL;
				left = NULL;
				full = true;
			}

			~Node()
			{
				allocator.destroy(&pair);
			}

	};

	template <class Pair, , class Key, class KeyGetter, class Compare = std::less<Key>, class Allocator = std::allocator<Pair>, class Allocator2 = std::allocator<Node<Pair> > >
	class Tree
	{

		public:
		
			typedef Pair 														value_type;
			typedef Key															key_type;
			typedef typename value_type::second_type							Data;
			typedef Node<Pair>													node;
			typedef node*														pointer;
			typedef typename ft::tree_iterator<node, value_type> 				iterator;
			typedef typename ft::tree_iterator<const node, const value_type> 	const_iterator;
			typedef ft::reverse_iterator<iterator>								reverse_iterator;
			typedef ft::reverse_iterator<const_iterator>						const_reverse_iterator;
			
			Tree(const Allocator& = Allocator(), const Allocator2& = Allocator2(), const Compare& comp = Compare())
			{
				this->_allocator_type = Allocator();
				this->_allocator_node = Allocator2();
				this->_compare = comp;
				this->_tree = this->_allocator_node.allocate(sizeof(node));
				this->_allocator_node.construct(this->_tree, Node<value_type>());
			}

			Tree(value_type value, const Allocator& = Allocator(), const Allocator2& = Allocator2(), const Compare& comp = Compare())
			{
				this->_allocator_type = Allocator();
				this->_allocator_node = Allocator2();
				this->_compare = comp;
				this->_tree = this->_allocator_node.allocate(sizeof(node));
				this->_allocator_node.construct(this->_tree, Node<value_type>(value));
			}

			Tree(const Tree &tree) : _tree(NULL)
			{
				*this = tree;
			}

			Tree&	operator=(const Tree& instance)
			{
				this->_allocator_type = instance._allocator_type;
				this->_allocator_node = instance._allocator_node;
				this->_compare = instance._compare;
				this->_tree = instance._tree;
			}

			~Tree()
			{
				destroyAndDeallocateAllNodes(this->_tree);
			}

			iterator 						begin()
			{
				iterator it(this->farLeftNode(this->tree()), this->tree());
				return it;
			}

			const_iterator 					begin() const
			{
				const_iterator it(this->farLeftNode(this->tree()), this->tree());
				return it;
			}

			iterator 						end()
			{
				iterator it;
				return it;
			}

			const_iterator 					end() const
			{
				const_iterator it;
				return it;
			}

			reverse_iterator 				rbegin()
			{
				iterator it(this->farRightNode(this->tree()), this->tree(), true, true);
				reverse_iterator rit(it);
				return rit;
			}
		
			const_reverse_iterator 			rbegin() const
			{
				const_iterator it(this->farRightNode(this->tree()), this->tree(), true, true);
				const_reverse_iterator rit(it);
				return rit;
			}
			
			reverse_iterator 				rend()
			{
				iterator it(this->farLeftNode(this->tree()), this->tree(), true, true);
				reverse_iterator rit(it);
				return rit;
			}
			
			const_reverse_iterator 			rend() const
			{
				const_iterator it(this->farLeftNode(this->tree()), this->tree(), true, true);
				const_reverse_iterator rit(it);
				return rit;
			}

			void destroyAndDeallocateAllNodes(pointer node)
			{
				if (node == NULL)
					return;
				destroyAndDeallocateAllNodes(node->right);
				pointer nodeleft = node->left;
				this->_allocator_node.destroy(node);
				this->_allocator_node.deallocate(node, sizeof(node));
				destroyAndDeallocateAllNodes(nodeleft);
			}

			key_type first()
			{
				return (this->_tree->pair.first);
			}

			Data second()
			{
				return (this->_tree->pair.second);
			}

			pointer rightRotate(pointer node)
			{
				pointer x = node->left; // noeud a mettre a la place de node
				pointer T2 = x->right; // place ou mettre node
				// pointer par1 = node->parent; // parent de node (noeud a mettre a droite)
				// pointer par2 = x; // parent du noeud a mettre a la place de node

				x->right = node;
				node->left = T2;
				// x->parent = par1;
				// node->parent = par2;
				// if (x->parent->left && x->parent->left->pair.first == node->pair.first)
				// 	x->parent->left = node->parent;
				// else
				// 	x->parent->right = node->parent;
				return x;
			}

			pointer leftRotate(pointer node)
			{
				pointer y = node->right;
				pointer t2 = y->left;
				// pointer par1 = node->parent;
				// pointer par2 = y;

				y->left = node;
				node->right = t2;
				// y->parent = par1;
				// node->parent = par2;
				// if (y->parent->right && y->parent->right->pair.first == node->pair.first)
				// 	y->parent->right = node->parent;
				// else
				// 	y->parent->left = node->parent;
				return y;
			}

			void insert(const value_type& x)
			{
				if (this->_tree != NULL && !this->_tree->full)
				{
					this->_allocator_type.destroy(&this->_tree->pair);
					this->_allocator_type.construct(&this->_tree->pair, ft::make_pair(x.first, x.second));
					this->_tree->full = true;
				}
				else
				{
					pointer newnode = this->_allocator_node.allocate(sizeof(node));
					this->_allocator_node.construct(newnode, Node<value_type>(x));
					newnode->full = true;

					pointer current = this->_tree;
					pointer svg;
					bool left;

					while (current != NULL)
					{
						svg = current;
						if (this->_compare(x, current->pair))
						{
							current = current->left;
							left = true;
						}
						else
						{
							current = current->right;
							left = false;
						}
					}
					if (left)
						svg->left = newnode;
					else
						svg->right = newnode;
					pointer subtree;
					bool isRoot;
					std::cout << "is Unbalanced ?" << std::endl;
					current = isUnbalanced(newnode->pair, &left, &isRoot, &subtree);
					if (current != NULL)
					{
						std::cout << "subtree->first == " << subtree->pair.first << std::endl;
						subtree = balanceSubTree(subtree);
						if (isRoot)
						{
							std::cout << "isRoot" << std::endl;
							this->_tree = subtree;
						}
						else if (left)
						{
							std::cout << "left" << std::endl;
							current->left = subtree;
						}
						else
						{
							std::cout << "right" << std::endl;
							current->right = subtree;
						}
					}
					// current = newnode;
					// current->parent = svg;
					// if (left)
					// 	current->parent->left = current;
					// else
					// 	current->parent->right = current;
					// balanceTree(newnode);
					// std::cout << "getHeight == " << getHeight(this->tree()) << std::endl;
					// pointer test = isUnbalanced2(newnode->pair.first);
					// if (test)
					// 	std::cout << "test == " << test->pair.first << std::endl;
				}
			}

			pointer balanceSubTree(pointer unba)
			{
				// pointer unba = isUnbalanced(current);
				// pointer unba = isUnbalanced2(current->pair.first);
				// if (unba != NULL)
				// {
					// std::cout << "unba == " << unba->pair.first << std::endl;
					int bf = getBalanceFactor(unba, 0);
					if (bf <= -2 && getBalanceFactor(unba->right, 0) <= -1)
					{
						// std::cout << "leftRotate" << std::endl;
						return leftRotate(unba);
					}
					else if (bf >= 2 && getBalanceFactor(unba->left, 0) >= 1)
					{
						// std::cout << "rightRotate" << std::endl;
					
						return rightRotate(unba);
					}
					else if (bf >= 2 && getBalanceFactor(unba->left, 0) <= -1)
					{
						// std::cout << "left right Rotate" << std::endl;
						unba->left = leftRotate(unba->left);
						return rightRotate(unba);
					}
					else if (bf <= -2 && getBalanceFactor(unba->right, 0) >= 1)
					{
						// std::cout << "right left Rotate" << std::endl;
						unba->right = rightRotate(unba->right);
						unba = leftRotate(unba);
						// std::cout << "unba == " << unba->pair.first << std::endl;
						// std::cout << "unba->right == " << unba->right->pair.first << std::endl;

						return (unba);
					}
					return unba;
				// }
			}

			int getHeight(pointer r)
			{
				if (r == NULL)
					return -1;
				int lheight = getHeight(r->left);
				int rheight = getHeight(r->right);
				if (lheight > rheight)
					return (lheight + 1);
				else
					return (rheight + 1);
			}

			int getBalanceFactor(pointer n, int one)
			{
  				// if (n == NULL)
     			// 	return -1;
				if (one)
   					return abs(getHeight(n->left) - getHeight(n->right));
				else
   					return (getHeight(n->left) - getHeight(n->right));
  			}

			pointer isUnbalanced(value_type value, bool *left, bool *isRoot, pointer *subtree)
			{
				pointer current = this->_tree;
				int height = getHeight(this->tree());
				pointer nodes[height];
				int i = 0;
				while (current != NULL && current->pair.first != value.first)
				{
					nodes[i++] = current;
					if (this->_compare(value, current->pair))
						current = current->left;
					else
						current = current->right;
				}
				for (i = i - 1; i > -1; i--)
				{
					if (getBalanceFactor(nodes[i], 1) > 1)
					{
						*subtree = nodes[i];
						if (i > 0)
						{
							*isRoot = false;
							if (nodes[i - 1]->right && nodes[i - 1]->right->pair.first == nodes[i]->pair.first)
								*left = false;
							else
								*left = true;
							return nodes[i - 1];
						}
						*isRoot = true;
						return (nodes[i]);
					}
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
				if (r->right != NULL)
				{
					for (int i = SPACE; i < space; i++)
						std::cout << " ";
					std::cout << "-" << std::endl;
					for (int i = SPACE; i < space; i++)
						std::cout << " ";
					std::cout << r->right->pair.first << std::endl;
				}
				if (r->left != NULL)
				{
					for (int i = SPACE; i < space; i++)
						std::cout << " ";
					std::cout << "-" << std::endl;
					for (int i = SPACE; i < space; i++)
						std::cout << " ";
					std::cout << r->left->pair.first << std::endl;
				}


			
				
				// if (r->parent != NULL)
				// {
				// 	for (int i = SPACE; i < space; i++)
				// 		std::cout << " ";
				// 	std::cout << "-" << std::endl;
				// 	for (int i = SPACE; i < space; i++)
				// 		std::cout << " ";
				// 	std::cout << r->parent->pair.first << std::endl;
				// 	for (int i = SPACE; i < space; i++)
				// 		std::cout << " ";
				// 	std::cout << r->parent->pair.second << std::endl;
				// }
				print2D(r->left, space);
			}

				void printInorder(pointer r) //  (Left, current node, Right)
				{
					if (r == NULL)
						return;
					printInorder(r->left);
					std::cout << r->pair.first << " "; 
					printInorder(r->right);
				}

				void printIndisorder(pointer r) //  (Left, current node, Right)
				{
					if (r == NULL)
						return;
					// static int i = 0;
					// std::cout << i++ << std::endl;
					printIndisorder(r->right);
					std::cout << r->pair.first << " ";
					printIndisorder(r->left);

				}

				void printPostorder(pointer r) //(Left, Right, Root)
				{
					if (r == NULL)
						return;
					// first recur on left subtree 
					printPostorder(r -> left);
					// then recur on right subtree 
					printPostorder(r -> right);
					// now deal with the node 
					std::cout << r -> pair.first << " ";
				}

				void printPreorder(pointer r) //(current node, Left, Right) 
				{
					if (r == NULL)
						return;
					std::cout << r->pair.first << " ";
					printPreorder(r -> left);
					printPreorder(r -> right);
				}

			bool isTreeEmpty()
			{
				if (this->_tree->full == false)
					return true;
				else
					return false;
			}

			pointer minValueNode(pointer node)
			{
  				pointer current = node;
    			while (current->left != NULL)
				{
     				current = current -> left;
				}
   				return current;
 			}

			void calldeleteNode(key_type k)
			{
				this->_tree = deleteNode(this->_tree, k);
			}

			void callFindKeyInValue(const key_type k)
			{
				pointer node = findKeyInTree(k);
				if (node == NULL)
					std::cout << "key " << k << " not found" << std::endl;
				else
				{
					std::cout << "key found ! ";
					std::cout << node->pair.first;
					std::cout << ", ";
					std::cout << node->pair.second << std::endl;
				}
			}

			pointer deleteNode(pointer r, key_type k)
			{
				if (r == NULL)
					return NULL;
				if (this->_compare(val, r->pair))
				{
					std::cout << "left : " << r->pair.first << std::endl;
					r->left = deleteNode(r->left, val);
				}
				else if (this->_compare(r->pair, val))
				{
					std::cout << "right : " << r->pair.first << std::endl;
					r->right = deleteNode(r->right, val);
				}
				else
				{
					if (r->left == NULL || r->right == NULL)
					{
						pointer tmp;
						if (r->left == NULL)
							tmp = r->right;
						else
							tmp = r->left;
						if (r == this->_tree && tmp == NULL)
						{
							tmp = this->_allocator_node.allocate(sizeof(node)); 
							this->_allocator_node.construct(tmp, Node<value_type>());
						}
						this->_allocator_node.destroy(r);
						this->_allocator_node.deallocate(r, sizeof(r));
						return tmp;
					}
					else
					{
						pointer tmp = minValueNode(r->right);
						this->_allocator_type.destroy(&r->pair);
						this->_allocator_type.construct(&r->pair, tmp->pair);
						r->right = deleteNode(r->right, tmp->pair);
					}
				}
				return (balanceSubTree(r));
			}

			pointer findKeyInTree(key_type k)
			{
				pointer current = this->tree();
				while (current != NULL && current->pair.first != value.first)
				{
					if (this->_compare(value, current->pair))
						current = current->left;
					else
						current = current->right;
				}
				return current;
			}

			pointer farLeftNode(pointer curr)
			{
				pointer current = curr;
				while (current->left != NULL)
					current = current->left;
				return (current);
			}

			pointer farRightNode(pointer curr)
			{
				pointer current = curr;
				while (current->right != NULL)
					current = current->right;
				return (current);
			}
		
		private:
		
			pointer				_tree;
			Allocator			_allocator_type;
			Allocator2			_allocator_node;
			Compare				_compare;

	};
}