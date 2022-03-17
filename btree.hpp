#pragma once

#include <iostream>
#include <cmath>
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
				full = true;
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
				this->_tree = this->_allocator_node.allocate(sizeof(node));
				this->_allocator_node.construct(this->_tree, Node<Key, T>());
			}

			Tree(Key key, T value, const Allocator& = Allocator(), const Allocator2& = Allocator2(), const Compare& comp = Compare())
			{
				this->_allocator_type = Allocator();
				this->_allocator_node = Allocator2();
				this->_compare = comp;
				this->_tree = this->_allocator_node.allocate(sizeof(node));
				this->_allocator_node.construct(this->_tree, Node<Key, T>(key, value));
			}

			~Tree()
			{
				destroyAndDeallocateAllNodes(this->_tree);
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

			typename ft::pair<const Key, T>::first_type first()
			{
				return (this->_tree->pair.first);
			}

			typename ft::pair<const Key, T>::second_type second()
			{
				return (this->_tree->pair.second);
			}

			pointer rightRotate(pointer node)
			{
				pointer x = node->left; // noeud a mettre a la place de node
				pointer T2 = x->right; // place ou mettre node
				pointer par1 = node->parent; // parent de node (noeud a mettre a droite)
				pointer par2 = x; // parent du noeud a mettre a la place de node

				x->right = node;
				node->left = T2;
				x->parent = par1;
				node->parent = par2;
				if (x->parent->left && x->parent->left->pair.first == node->pair.first)
					x->parent->left = node->parent;
				else
					x->parent->right = node->parent;
				return x;
			}

			pointer leftRotate(pointer node)
			{
				pointer y = node->right;
				pointer t2 = y->left;
				pointer par1 = node->parent;
				pointer par2 = y;

				y->left = node;
				node->right = t2;
				y->parent = par1;
				node->parent = par2;
				if (y->parent->right && y->parent->right->pair.first == node->pair.first)
					y->parent->right = node->parent;
				else
					y->parent->left = node->parent;
				return y;
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
					pointer newnode = this->_allocator_node.allocate(sizeof(node));
					this->_allocator_node.construct(newnode, Node<Key, T>(x.first, x.second));
					newnode->full = true;

					pointer current = this->_tree;
					pointer svg;
					bool left;

					while (current != NULL)
					{
						svg = current;
						if (this->_compare(x.first, current->pair.first))
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
					current = newnode;
					current->parent = svg;
					if (left)
						current->parent->left = current;
					else
						current->parent->right = current;
					balanceTree(current);
				}
			}

			void balanceTree(pointer current)
			{
				pointer unba = isUnbalanced(current);
				if (unba != NULL)
				{
					int bf = getBalanceFactor(unba, 0);
					if (bf <= -2 && getBalanceFactor(unba->right, 0) <= -1)
					{
						std::cout << "1" << std::endl;
						unba = leftRotate(unba);
					}
					else if (bf >= 2 && getBalanceFactor(unba->left, 0) >= 1)
					{
						std::cout << "2" << std::endl;
					
						unba = rightRotate(unba);
					}
					else if (bf >= 2 && getBalanceFactor(unba->left, 0) <= -1)
					{

						std::cout << "3" << std::endl;

						unba->left = leftRotate(unba->left);
						unba = rightRotate(unba);
					}
					else if (bf <= -2 && getBalanceFactor(unba->right, 0) >= 1)
					{
						std::cout << "4" << std::endl;

						unba->right = rightRotate(unba->right);
						unba = leftRotate(unba);
					}
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

			int getBalanceFactor(pointer n, int one)
			{
  				// if (n == NULL)
     			// 	return -1;
				if (one)
   					return abs(height(n->left) - height(n->right));
				else
   					return (height(n->left) - height(n->right));
  			}

			pointer isUnbalanced(pointer curr)
			{
				while (curr != NULL)
				{
					if (getBalanceFactor(curr, 1) > 1)
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

			// void printPostorder(pointer r) //(Left, Right, Root)
			// {
			// 	static int i = 0;
			// 	std::cout << ++i << std::endl;

				
			// 	if (r == NULL)
			// 		return;
			// 	if (getBalanceFactor(r, 1) > 1)
			// 	{
			// 		std::cout << r->pair.first << " ";
			// 		return ;
			// 	}
			// 	// first recur on left subtree 
			// 	printPostorder(r->left);
			// 	// then recur on right subtree 
			// 	printPostorder(r->right);
			// 	// now deal with the node
			// }

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

			void calldeleteNode(Key k)
			{
				this->_tree = deleteNode(this->_tree, k);
			}

			pointer deleteNode(pointer r, Key k)
			{
				// base case 
				if (r == NULL)
					return NULL;
				if (this->_compare(k, r->pair.first))
					r->left = deleteNode(r->left, k);
				else if (!this->_compare(k, r->pair.first))
					r->right = deleteNode(r->right, k);
				// if key is same as root's key, then This is the node to be deleted 
				else
				{
					// node with only one child or no child 
					if (r->left == NULL)
					{
						pointer tmp = r->right;
						tmp->parent = r->parent;
						this->_allocator_node.destroy(r);
						this->_allocator_node.deallocate(r, sizeof(r));
						return tmp;
					}
					else if (r->right == NULL)
					{
						pointer tmp = r->left;
						tmp->parent = r->parent;
						this->_allocator_node.destroy(r);
						this->_allocator_node.deallocate(r, sizeof(r));
						return tmp;
					}
					else
					{
						// node with two children: Get the inorder successor (smallest in the right subtree) 
						pointer tmp = minValueNode(r->right);

						// Copy the inorder successor's content to this node

						this->_allocator_type.destroy(&r->pair);
						this->_allocator_type.construct(&r->pair, tmp->pair);

						// Delete the inorder successor 
						r->right = deleteNode(r->right, tmp->pair.first);
						//deleteNode(r->right, temp->value); 
					}
				}
				int bf = getBalanceFactor(r, 0);
				// Left Left Imbalance/Case or Right rotation 
				if (bf == 2 && getBalanceFactor(r -> left, 0) >= 0)
					return rightRotate(r);
				// Left Right Imbalance/Case or LR rotation 
				else if (bf == 2 && getBalanceFactor(r -> left, 0) == -1)
				{
					r -> left = leftRotate(r -> left);
					return rightRotate(r);
				}
				// Right Right Imbalance/Case or Left rotation	
				else if (bf == -2 && getBalanceFactor(r -> right, 0) <= -0)
					return leftRotate(r);
				// Right Left Imbalance/Case or RL rotation 
				else if (bf == -2 && getBalanceFactor(r -> right, 0) == 1)
				{
					r -> right = rightRotate(r -> right);
					return leftRotate(r);
				}
				return r;
			}



//   void printPreorder(Treepointer  r) //(current node, Left, Right) 
//   {
//     if (r == NULL)
//       return;
//     /* first print data of pointer /
//     cout << r->pair.first << " ";
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