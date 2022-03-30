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

		node_pointer								current;
		node_pointer								root;

		tree_iterator() : current(NULL), root(NULL), _isRev(false), _isEnd(false) {}

		tree_iterator(node_pointer node, node_pointer tree, bool isRev = false, bool end = false)
		: current(node), root(tree), _isRev(isRev), _isEnd(end) {}

		tree_iterator(const tree_iterator& instance)
		{
			*this = instance;
		}

		template<class U, class V>
		tree_iterator(const tree_iterator<U, V, KeyGetter>& instance)
		{
			*this = instance;
		}

		bool getisEnd() const
		{
			return this->_isEnd;
		}

		bool getisRev() const
		{
			return this->_isRev;
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

		template<class U, class V>
		tree_iterator& operator=(const tree_iterator<U, V, KeyGetter>& instance)
		{
			this->current = instance.current;
			this->root = instance.root;
			this->_isRev = instance.getisRev();
			this->_isEnd = instance.getisEnd();
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
		KeyGetter		_getter;

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
			while (curr != NULL && _getter(curr->pair) != _getter(current->pair))
			{
				nodes[i++] = curr;
				if (this->current->compare(_getter(current->pair), _getter(curr->pair)))
					curr = curr->left;
				else
					curr = curr->right;
			}
			i--;
			if (current->left == NULL)
			{
				while (i > -1 && this->current->compare(_getter(current->pair), _getter(nodes[i]->pair)))
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
			while (curr != NULL && _getter(curr->pair) != _getter(current->pair))
			{
				nodes[i++] = curr;
				if (this->current->compare(_getter(current->pair), _getter(curr->pair)))
					curr = curr->left;
				else
					curr = curr->right;
			}
			i--;
			if (current->right == NULL)
			{
				while (i > -1 && this->current->compare(_getter(nodes[i]->pair), _getter(this->current->pair)))
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

 	template<class Tx, class Ux, class Ty, class Uy, class KG>
	bool	operator==(const tree_iterator<Tx, Ux, KG>& x, const tree_iterator<Ty, Uy, KG>& y)
	{
		return (x.current == y.current);
	}

	template<class Tx, class Ux, class Ty, class Uy, class KG>
	bool	operator!=(const tree_iterator<Tx, Ux, KG>& x, const tree_iterator<Ty, Uy, KG>& y)
	{
		return (x.current != y.current);
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

			void balance_function (pointer newnode, bool left)
			{
				pointer subtree;
				bool isRoot;
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
				
		public:

			explicit Tree(const Compare& comp = Compare(), const Allocator& = Allocator(), const Allocator2& = Allocator2())
			{
				this->_allocator_type = Allocator();
				this->_allocator_node = Allocator2();
				this->_compare = comp;
				this->_tree = this->try_allocation_node(sizeof(node));
				this->_allocator_node.construct(this->_tree, Node<value_type, key_compare>());
				this->_size = 0;
			}

			Tree(value_type value, const Compare& comp = Compare(), const Allocator& = Allocator(), const Allocator2& = Allocator2())
			{
				this->_allocator_type = Allocator();
				this->_allocator_node = Allocator2();
				this->_compare = comp;
				this->_tree = this->try_allocation_node(sizeof(node));
				this->_allocator_node.construct(this->_tree, Node<value_type, key_compare>(value));
				this->_size = 1;
			}

			Tree(const Tree &tree) : _tree(NULL), _size(0)
			{
				*this = tree;
			}

			Tree&	operator=(const Tree& instance)
			{
				this->_allocator_type = instance._allocator_type;
				this->_allocator_node = instance._allocator_node;
				this->_compare = instance._compare;
				if (this->_tree != NULL)
				{
					this->destroyAndDeallocateAllNodes(this->_tree);
				}
				this->_tree = this->try_allocation_node(sizeof(node));
				this->_allocator_node.construct(this->_tree, Node<value_type, key_compare>());
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

			void insert(const value_type& x)
			{
				if (this->_tree != NULL && !this->_tree->full)
				{
					this->_allocator_type.destroy(&this->_tree->pair);
					this->_allocator_type.construct(&this->_tree->pair, ft::make_pair(x.first, x.second));
					this->_tree->full = true;
					this->_size++;
				}
				else
				{
					pointer newnode = this->try_allocation_node(sizeof(node));
					this->_allocator_node.construct(newnode, Node<value_type, key_compare>(x));
					newnode->full = true;
					this->_size++;

					pointer current = this->_tree;
					pointer svg;
					bool left;

					while (current != NULL)
					{
						svg = current;
						if (this->_compare(_getter(x), _getter(current->pair)))
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
					this->balance_function(newnode, left);
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

			iterator insert(iterator position, const value_type &x)
			{
				pointer newnode = this->try_allocation_node(sizeof(node));
				this->_allocator_node.construct(newnode, Node<value_type, key_compare>(x));
				newnode->full = true;

				pointer current = position.current;
				pointer svg;
				bool left;

				if (current == NULL)
				{
					this->_allocator_node.destroy(newnode);
					this->_allocator_node.deallocate(newnode, sizeof(newnode));
					insert(x);
				}
				else
				{
					this->_size++;
					while (current != NULL)
					{
						svg = current;
						if (this->_compare(_getter(x), _getter(current->pair)))
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
					this->balance_function(newnode, left);
				}
				return this->findKeyPositionInTree(_getter(x));
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

			pointer isUnbalanced(key_type k, bool *left, bool *isRoot, pointer *subtree)
			{
				pointer current = this->_tree;
				int height = getHeight(this->tree());
				pointer nodes[height];
				int i = 0;
				while (current != NULL && current->pair.first != k)
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
					if (!this->_compare(x, _getter(*it)))
						return it;
				}
				return it;
			}

			pair<iterator,iterator>				equal_range(const key_type& x)
			{
				iterator itlow = this->lower_bound(x);
				iterator itup = this->upper_bound(x);
				return ft::make_pair(itlow, itup);
			}

			pair<const_iterator,const_iterator>	equal_range(const key_type& x) const
			{
				const_iterator itlow = this->lower_bound(x);
				const_iterator itup = this->upper_bound(x);
				return ft::make_pair(itlow, itup);
			}

			void print2D(pointer r, int space = 0)
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
				if (this->_compare(k, _getter(r->pair)))
				{
					r->left = deleteNode(r->left, k);
				}
				else if (this->_compare(_getter(r->pair), k))
				{
					r->right = deleteNode(r->right, k);
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
							tmp = this->try_allocation_node(sizeof(node));
							this->_allocator_node.construct(tmp, Node<value_type, key_compare>());
						}
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
				return (balanceSubTree(r));
			}

			pointer findKeyInTree(const key_type k) const
			{
				pointer current = this->tree();
				while (current != NULL && _getter(current->pair) != k)
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
				while (current != this->end() && _getter(*current) != k)
				{
					current++;
				}
				return current;
			}

			const_iterator findKeyPositionInTreeConst(const key_type k) const
			{
				const_iterator current = this->begin();
				while (current != this->end() && _getter(*current) != k)
				{
					current++;
				}
				return current;
			}

			pointer farLeftNode(pointer curr) const
			{
				pointer current = curr;
				while (current->left != NULL)
					current = current->left;
				return (current);
			}

			pointer farRightNode(pointer curr) const
			{
				pointer current = curr;
				while (current->right != NULL)
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