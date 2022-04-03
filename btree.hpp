#pragma once

#include <iostream>
#include <cmath>
#include "utils.hpp"
#include "iterator.hpp"
#include "functional.hpp"

#define SPACE 10

namespace ft
{

	template<class Node, class Value, class KeyGetter>
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

		private:
	
		node_pointer	_current;
		node_pointer	_root;
		node_pointer	_end;
		KeyGetter		_getter;

		public:

		tree_iterator() : _current(NULL), _root(NULL), _end(NULL) {}

		tree_iterator(node_pointer end, node_pointer tree) : _current(end), _root(tree), _end(end) {}
		
		tree_iterator(node_pointer node, node_pointer tree, node_pointer end)
		: _current(node), _root(tree), _end(end) {}

		tree_iterator(const tree_iterator& instance)
		{
			*this = instance;
		}

		template<class U, class V>
		tree_iterator(const tree_iterator<U, V, KeyGetter>& instance)
		{
			*this = instance;
		}

		node_pointer getRoot() const
		{
			return this->_root;
		}

		node_pointer base() const
		{
			return this->_current;
		}

		node_pointer getEnd() const
		{
			return this->_end;
		}

		~tree_iterator() {}

		tree_iterator& operator=(const tree_iterator& instance)
		{
			this->_current = instance._current;
			this->_root = instance._root;
			this->_end = instance._end;
			return *this;
		}

		template<class U, class V>
		tree_iterator& operator=(const tree_iterator<U, V, KeyGetter>& instance)
		{
			this->_current = instance.base();
			this->_root = instance.getRoot();
			this->_end = instance.getEnd();
			return *this;
		}

		reference operator*() const
		{
			return (this->_current->pair);
		}

      	pointer operator->() const
		{
			return (&this->operator*());
		}
 
      	tree_iterator& operator++()
    	{
			this->_current = this->increase();
			return *this;
      	}

      	tree_iterator operator++(int)
      	{
			tree_iterator tmp = *this;
			this->_current = this->increase();
			return tmp;
	  	}

     	tree_iterator& operator--()
      	{
			this->_current = this->decrease();
			return *this;
      	}
		
		tree_iterator operator--(int)
      	{
			tree_iterator tmp = *this;
			this->_current = this->decrease();
			return tmp;
	  	}

		private:

		bool equal_null(node_pointer curr) const
		{
			return (curr == NULL || curr == this->_end);
		}

		bool no_null(node_pointer curr) const
		{
			return (curr != NULL && curr != this->_end);
		}

		node_pointer decrease()
		{
			node_pointer curr = this->_root;
			int height = this->getHeight(curr);
			node_pointer nodes[height];
			int i = 0;
 
			// while (curr != NULL && _getter(curr->pair) != _getter(_current->pair))
			while (no_null(curr) && _getter(curr->pair) != _getter(_current->pair))
			{
				nodes[i++] = curr;
				// if (this->_current->compare(_getter(_current->pair), _getter(curr->pair)))
				if (this->_current != this->_end && this->_current->compare(_getter(_current->pair), _getter(curr->pair)))
					curr = curr->left;
				else
					curr = curr->right;
			}
			i--;
			// if (_current->left == NULL)
			if (equal_null(_current) && no_null(nodes[i]))
				return this->farRightNode(nodes[i]);
			if (equal_null(_current->left))
			{
				while (i > -1 && this->_current->compare(_getter(_current->pair), _getter(nodes[i]->pair)))
					i--;
				if (i > -1)
					return nodes[i];
			}
			// else
			// {
			return this->farRightNode(this->_current->left);
			// }
			// return NULL;
		}

		node_pointer increase()
		{
			node_pointer curr = this->_root;
			int height = this->getHeight(curr);
			node_pointer nodes[height];
			int i = 0;
			
			// while (curr != NULL && _getter(curr->pair) != _getter(_current->pair))
			while (no_null(curr) && _getter(curr->pair) != _getter(_current->pair))
			{
				nodes[i++] = curr;
				// this->_current->compare(_getter(_current->pair), _getter(curr->pair))
				if (this->_current != this->_end && this->_current->compare(_getter(_current->pair), _getter(curr->pair)))
					curr = curr->left;
				else
					curr = curr->right;
			}
			i--;
			// if (_current->right == NULL)
			if (equal_null(_current) && i > -1 && no_null(nodes[i]))
				return this->farLeftNode(nodes[i]);
			if (equal_null(_current->right))
			{
				while (i > -1 && this->_current->compare(_getter(nodes[i]->pair), _getter(this->_current->pair)))
					i--;
				if (i > -1)
					return nodes[i];
			}
			// else
			// {
			return this->farLeftNode(this->_current->right);
			// }
			// return NULL;
		}

		node_pointer farLeftNode(node_pointer curr)
		{
			node_pointer current = curr;
			// while (current->left != NULL)
			while (no_null(current->left))
				current = current->left;
			return (current);
		}

		node_pointer farRightNode(node_pointer curr)
		{
			node_pointer current = curr;
			// while (current->right != NULL)
			while (no_null(current->right))
				current = current->right;
			return (current);
		}

		int getHeight(node_pointer r)
		{
			// if (r == NULL)
			if (equal_null(r))
				return -1;
			int lheight = getHeight(r->left);
			int rheight = getHeight(r->right);
			if (lheight > rheight)
				return (lheight + 1);
			else
				return (rheight + 1);
		}
  };

 	template<class Tx, class Ux, class Ty, class Uy, class KG>
	bool	operator==(const tree_iterator<Tx, Ux, KG>& x, const tree_iterator<Ty, Uy, KG>& y)
	{
		return (x.base() == y.base());
	}

	template<class Tx, class Ux, class Ty, class Uy, class KG>
	bool	operator!=(const tree_iterator<Tx, Ux, KG>& x, const tree_iterator<Ty, Uy, KG>& y)
	{
		return (x.base() != y.base());
	}

	template <class Pair, class Compare, class Allocator = std::allocator<Pair> >
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

			Node(Pair value, const Allocator& = Allocator(), const Compare& = Compare())
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

	template <class Pair, class Key, class KeyGetter, class Compare = std::less<Key>, class Allocator = std::allocator<Pair>, class Allocator2 = std::allocator<Node<Pair, Compare> > >
	class Tree
	{
		public:
		
			typedef Pair 																	value_type;
			typedef Key																		key_type;
			typedef Compare																	key_compare;
			typedef typename value_type::second_type										Data;
			typedef Node<Pair, Compare>														node;
			typedef node*																	pointer;
			typedef typename ft::tree_iterator<node, value_type, KeyGetter> 				iterator;
			typedef typename ft::tree_iterator<const node, const value_type, KeyGetter> 	const_iterator;
			typedef ft::reverse_iterator<iterator>											reverse_iterator;
			typedef ft::reverse_iterator<const_iterator>									const_reverse_iterator;
			
		private:
		
			pointer				_tree;
			pointer				_sentry;
			Allocator			_allocator_type;
			Allocator2			_allocator_node;
			key_compare			_compare;
			KeyGetter			_getter;
			std::size_t			_size;

			pointer try_allocation_node(size_t n)
			{
				pointer tmp;
				try
				{
					tmp = this->_allocator_node.allocate(n);
				}
				catch(const std::bad_alloc& ba)
				{
					std::cerr << ba.what() << std::endl;
				}
				return tmp;
			}

			void place_sentry_at_end(void)
			{
				pointer farRight = this->farRightNode(this->_tree);
				// std::cout << "farRight == " << farRight->pair.first << std::endl;
				if (farRight->right != this->_sentry)
				{
					// std::cout << "NO END IN FAR RIGHT" << std::endl;
					farRight->right = this->_sentry;
				}
			}

			void balance_function (pointer newnode)
			{
				pointer subtree;
				bool isRoot;
				bool left;
				pointer current = isUnbalanced(_getter(newnode->pair), &left, &isRoot, &subtree);
				if (current != NULL)
				{
					subtree = balanceSubTree(subtree);
					if (isRoot)
					{
						this->_tree = subtree;
					}
					else if (left)
					{
						current->left = subtree;
					}
					else
					{
						current->right = subtree;
					}
				}
				place_sentry_at_end();
			}

			pointer find_parent(iterator position)
			{
				iterator it = this->begin();
				for (; it != this->end(); it++)
				{
					if (it.current->left && _getter(it.current->left->pair) == _getter(*position))
						return it.current;
					else if (it.current->right && _getter(it.current->right->pair) == _getter(*position))
						return it.current;
				}
				return it.current;
			}

			pointer create_node(const value_type& x)
			{
				pointer newnode = this->try_allocation_node(sizeof(node));
				this->_allocator_node.construct(newnode, Node<value_type, key_compare>(x));
				newnode->full = true;
				this->_size++;
				// std::cout << "newnode->pair.first == " << newnode->pair.first << std::endl;
				// std::cout << "newnode->compare ==    " << newnode->compare(newnode->pair.first, newnode->pair.first) << std::endl;
				return newnode;
			}

			void insert_node(pointer newnode, pointer position)
			{
				pointer current = position;
				pointer svg;
				bool left;

				while (no_null(current))
				{
					svg = current;
					if (this->_compare(_getter(newnode->pair), _getter(current->pair)))
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
				// std::cout << "svg == " << svg->pair.first << std::endl;
				if (left)
					svg->left = newnode;
				else
					svg->right = newnode;
			}

			bool ft_compare(const value_type &a, const value_type &b) const
			{
				return this->_compare(_getter(a), _getter(b));
			}

			bool equal_null(const pointer curr) const
			{
				return (curr == NULL || curr == this->_sentry);
			}

			bool no_null(const pointer curr) const
			{
				return (curr != NULL && curr != this->_sentry);
			}
				
		public:

			explicit Tree(const Compare& comp = Compare(), const Allocator& = Allocator(), const Allocator2& = Allocator2())
			{
				this->_allocator_type = Allocator();
				this->_allocator_node = Allocator2();
				this->_compare = comp;
				this->_sentry = this->try_allocation_node(sizeof(node));
				this->_allocator_node.construct(this->_sentry, Node<value_type, key_compare>());
				this->_tree = this->_sentry;
				this->_size = 0;
			}

			Tree(value_type value, const Compare& comp = Compare(), const Allocator& = Allocator(), const Allocator2& = Allocator2())
			{
				this->_allocator_type = Allocator();
				this->_allocator_node = Allocator2();
				this->_compare = comp;
				this->_sentry = this->try_allocation_node(sizeof(node));
				this->_allocator_node.construct(this->_sentry, Node<value_type, key_compare>());

				this->_tree = this->try_allocation_node(sizeof(node));
				this->_allocator_node.construct(this->_tree, Node<value_type, key_compare>(value));

				this->_tree->right = this->_sentry;

				this->_size = 1;
			}

			Tree(const Tree &tree) : _tree(NULL), _sentry(NULL), _size(0)
			{
				*this = tree;
			}

			Tree&	operator=(const Tree& instance)
			{
				this->_allocator_type = instance._allocator_type;
				this->_allocator_node = instance._allocator_node;
				this->_compare = instance._compare;
				if (this->_tree == NULL)
				{
					this->_sentry = this->try_allocation_node(sizeof(node));
					this->_allocator_node.construct(this->_sentry, *instance._sentry);
				}
				else
				{
					this->destroyAndDeallocateAllNodes(this->_tree);
				}
				this->_tree = this->_sentry;
				for (const_iterator it = instance.begin(); it != instance.end(); it++)
				{
					this->insert(*it);
				}
				this->_size = instance._size;
				return *this;
			}

			~Tree()
			{
				destroyAndDeallocateAllNodes(this->_tree);
				this->_allocator_node.destroy(this->_sentry);
				this->_allocator_node.deallocate(this->_sentry, sizeof(node));
			}

			iterator 						begin()
			{
				iterator it(this->farLeftNode(this->tree()), this->tree(), this->_sentry);
				return it;
			}

			const_iterator 					begin() const
			{
				const_iterator it(this->farLeftNode(this->tree()), this->tree(), this->_sentry);
				return it;
			}

			iterator 						end()
			{
				iterator it(this->_sentry, this->tree());
				return it;
			}

			const_iterator 					end() const
			{
				const_iterator it(this->_sentry, this->tree());
				return it;
			}

			reverse_iterator 				rbegin()
			{
				iterator it(this->_sentry, this->tree());
				reverse_iterator rit(it);
				return rit;
			}
		
			const_reverse_iterator 			rbegin() const
			{
				const_iterator it(this->_sentry, this->tree());
				const_reverse_iterator rit(it);
				return rit;
			}
			
			reverse_iterator 				rend()
			{
				iterator it(this->farLeftNode(this->tree()), this->tree(), this->_sentry);
				reverse_iterator rit(it);
				return rit;
			}
			
			const_reverse_iterator 			rend() const
			{
				const_iterator it(this->farLeftNode(this->tree()), this->tree(), this->_sentry);
				const_reverse_iterator rit(it);
				return rit;
			}

			void destroyAndDeallocateAllNodes(pointer node)
			{
				if (equal_null(node))
					return;
				destroyAndDeallocateAllNodes(node->right);
				pointer nodeleft = node->left;
				this->_allocator_node.destroy(node);
				this->_allocator_node.deallocate(node, sizeof(node));
				destroyAndDeallocateAllNodes(nodeleft);
			}

			key_type first() const
			{
				return (this->_tree->pair.first);
			}

			Data second() const
			{
				return (this->_tree->pair.second);
			}

			std::size_t size() const
			{
				return this->_size;
			}

			Allocator get_allocator_type() const
			{
				return this->_allocator_type;
			}

			Allocator2 get_allocator_node() const
			{
				return this->_allocator_node;
			}

			key_compare	get_compare() const
			{
				return this->_compare;
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

			void 							swap(Tree& x)
			{
				std::swap(this->_tree, x._tree);
				std::swap(this->_allocator_type, x._allocator_type);
				std::swap(this->_allocator_node, x._allocator_node);
				std::swap(this->_compare, x._compare);
				std::swap(this->_getter, x._getter);
				std::swap(this->_size, x._size);
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

			iterator insert(const value_type& x)
			{
				// if (this->_tree != NULL && !this->_tree->full)
				if (this->_tree == this->_sentry)
				{
					// this->_allocator_type.destroy(&this->_tree->pair);
					// this->_allocator_type.construct(&this->_tree->pair, ft::make_pair(x.first, x.second));
					// this->_tree->full = true;
					// this->_size++;
					this->_tree = create_node(x);
					this->_tree->right = this->_sentry;
				}
				else
				{
					// std::cout << "insert else" << std::endl;
					pointer newnode = create_node(x);
					// std::cout << "newnode == " << newnode->pair.first << std::endl;
					insert_node(newnode, this->_tree);
					balance_function(newnode);
					// std::cout << "end of insert else" << std::endl;
				}
				return this->findKeyPositionInTree(x.first);
			}

			iterator insert(iterator hint, const value_type& x)
			{
				if (hint == this->begin())
				{
					if (_size && ft_compare(x, *hint))
					{
						pointer newnode = create_node(x);
						this->insert_node(newnode, hint.base());
						balance_function(newnode);
						return this->findKeyPositionInTree(x.first);
					}
					return this->insert(x);
				}
				if (hint == this->end())
				{
					pointer rightMost = farRightNode(this->_tree);
					if (ft_compare(rightMost->pair, x))
					{
						pointer newnode = create_node(x);
						this->insert_node(newnode, rightMost);
						balance_function(newnode);
						return this->findKeyPositionInTree(x.first);
					}
					return this->insert(x);
				}
				iterator prev = hint;
				--prev;
				if (ft_compare(prev.base()->pair, x) && ft_compare(x, hint.base()->pair))
				{
					pointer newnode = create_node(x);
					if (prev.base()->right != NULL)
					{
						this->insert_node(newnode, hint.base());
						balance_function(newnode);
						return this->findKeyPositionInTree(x.first);
					}
					this->insert_node(newnode, prev.base());
					balance_function(newnode);
					return this->findKeyPositionInTree(x.first);
				}
				return this->insert(x);
			}

			pointer balanceSubTree(pointer unba)
			{
				int bf = getBalanceFactor(unba, 0);
				if (bf <= -2 && getBalanceFactor(unba->right, 0) <= -1)
				{
					return leftRotate(unba);
				}
				else if (bf >= 2 && getBalanceFactor(unba->left, 0) >= 1)
				{
					return rightRotate(unba);
				}
				else if (bf >= 2 && getBalanceFactor(unba->left, 0) <= -1)
				{
					unba->left = leftRotate(unba->left);
					return rightRotate(unba);
				}
				else if (bf <= -2 && getBalanceFactor(unba->right, 0) >= 1)
				{
					unba->right = rightRotate(unba->right);
					return leftRotate(unba);
				}
				return unba;
			}

			int getHeight(pointer r)
			{
				// if (r == NULL)
				if (equal_null(r))
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
				if (one)
   					return abs(getHeight(n->left) - getHeight(n->right));
				else
   					return (getHeight(n->left) - getHeight(n->right));
  			}

			pointer isUnbalanced(key_type k, bool *left, bool *isRoot, pointer *subtree)
			{
				pointer current = this->_tree;
				int height = getHeight(this->tree());
				pointer nodes[height];
				int i = 0;
				// while (current != NULL && current->pair.first != k) 
				while (no_null(current) && _getter(current->pair) != k)
				{
					nodes[i++] = current;
					if (this->_compare(k, _getter(current->pair)))
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
							// if (nodes[i - 1]->right && nodes[i - 1]->right->pair.first == nodes[i]->pair.first)
							if (no_null(nodes[i - 1]->right) && _getter(nodes[i - 1]->right->pair) == _getter(nodes[i]->pair))
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
			
			pointer tree() const
			{
				return (this->_tree);
			}

			iterator 							lower_bound(const key_type& x)
			{
				iterator it = this->findKeyPositionInTree(x);
				for (; it != this->end(); it++)
				{
					if (!this->_compare(_getter(*it), x))
						return it;
				}
				return it;
			}

			const_iterator 						lower_bound(const key_type& x) const
			{
				const_iterator it = this->findKeyPositionInTreeConst(x);
				for (; it != this->end(); it++)
				{
					if (!this->_compare(_getter(*it), x))
						return it;
				}
				return it;
			}

			iterator 							upper_bound(const key_type& x)
			{
				iterator it = this->findKeyPositionInTree(x);
				for (; it != this->end(); it++)
				{
					if (this->_compare(x, _getter(*it)))
						return it;
				}
				return it;
			}

			const_iterator 						upper_bound(const key_type& x) const
			{
				const_iterator it = this->findKeyPositionInTreeConst(x);
				for (; it != this->end(); it++)
				{
					if (this->_compare(x, _getter(*it)))
						return it;
				}
				return it;
			}

			pair<iterator,iterator>				equal_range(const key_type& x)
			{
				return ft::make_pair(lower_bound(x), upper_bound(x));
			}

			pair<const_iterator,const_iterator>	equal_range(const key_type& x) const
			{
				return ft::make_pair(lower_bound(x), upper_bound(x));
			}

			void print2D(pointer r, int space = 0)
			{
				// if (r == NULL)
				if (equal_null(r))
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
					// if (r == NULL)
					if (equal_null(r))
						return;
					printInorder(r->left);
					std::cout << r->pair.first << " "; 
					printInorder(r->right);
				}

				void printIndisorder(pointer r) //  (Left, current node, Right)
				{
					// if (r == NULL)
					if (equal_null(r))
						return;
					// static int i = 0;
					// std::cout << i++ << std::endl;
					printIndisorder(r->right);
					std::cout << r->pair.first << " ";
					printIndisorder(r->left);

				}

				void printPostorder(pointer r) //(Left, Right, Root)
				{
					// if (r == NULL)
					if (equal_null(r))
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
					// if (r == NULL)
					if (equal_null(r))
						return;
					std::cout << r->pair.first << " ";
					printPreorder(r -> left);
					printPreorder(r -> right);
				}

			bool isTreeEmpty()
			{
				return (this->_tree->full == false);
			}

			pointer minValueNode(pointer node)
			{
  				pointer current = node;
    			// while (current->left != NULL)
    			while (no_null(current->left))
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
				// if (node == NULL)
				if (equal_null(node))
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
				if (equal_null(r))
					return NULL;
				if (this->_compare(k, _getter(r->pair)))
					r->left = deleteNode(r->left, k);
				else if (this->_compare(_getter(r->pair), k))
					r->right = deleteNode(r->right, k);
				else
				{
					if (equal_null(r->left) || equal_null(r->right))
					{
						pointer tmp = equal_null(r->left) ? r->right : r->left;
						if (r == this->_tree && equal_null(tmp))
							tmp = this->_sentry;
						this->_allocator_node.destroy(r);
						this->_allocator_node.deallocate(r, sizeof(r));
						this->_size--;
						return tmp;
					}
					else
					{
						pointer tmp = minValueNode(r->right);
						this->_allocator_type.destroy(&r->pair);
						this->_allocator_type.construct(&r->pair, tmp->pair);
						r->right = deleteNode(r->right, _getter(tmp->pair));
					}
				}
				r = balanceSubTree(r);
				place_sentry_at_end();
				return r;
			}

			pointer findKeyInTree(const key_type k) const
			{
				pointer current = this->tree();
				// while (current != NULL && _getter(current->pair) != k)
				while (no_null(current) && _getter(current->pair) != k)
				{
					if (this->_compare(k, _getter(current->pair)))
						current = current->left;
					else
						current = current->right;
				}
				return current;
			}

			iterator findKeyPositionInTree(const key_type k)
			{
				iterator current = this->begin();
				// while (current != this->end() && _getter(*current) != k)
				while ((current != this->end() && current.base() != NULL) && _getter(*current) != k)
				{
					// std::cout << "key pos in tree current == " << current->first << std::endl;
					current++;
				}
				// std::cout << "return current" << std::endl;
				return current;
			}

			const_iterator findKeyPositionInTreeConst(const key_type k) const
			{
				const_iterator current = this->begin();
				// while (current != this->end() && _getter(*current) != k)
				while ((current != this->end() && current.base() != NULL) && _getter(*current) != k)
				{
					current++;
				}
				return current;
			}

			pointer farLeftNode(pointer curr) const
			{
				pointer current = curr;
				// while (current->left != NULL)
				while (no_null(current->left))
					current = current->left;
				return (current);
			}

			pointer farRightNode(pointer curr) const
			{
				pointer current = curr;
				// while (current->right != NULL)
				while (no_null(current->right))
					current = current->right;
				return (current);
			}

			friend bool operator==(const Tree& x, const Tree& y)
			{
				return x._size == y._size && ft::equal(x.begin(), x.end(), y.begin());
			}
	
			friend bool operator<(const Tree& x, const Tree& y)
			{
				return ft::lexicographical_compare(x.begin(), x.end(), y.begin(), y.end());
			}

	};
}