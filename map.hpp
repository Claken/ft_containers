#pragma once

#include <iostream>
#include "utils.hpp"
#include "iterator.hpp"
#include "btree.hpp"
#include "functional.hpp"

namespace ft
{
	template <class Key, class T, class Compare = std::less<Key>, class Allocator = std::allocator<ft::pair<const Key, T> > >
		class map
		{
			public:
		
				// types:
					typedef Key 										key_type;
					typedef T 											mapped_type;
					typedef ft::pair<const Key, T> 						value_type;
					typedef Compare 									key_compare;
					typedef Allocator 									allocator_type;
					typedef typename Allocator::reference 				reference;
					typedef typename Allocator::const_reference 		const_reference;
					typedef std::size_t 								size_type;
					typedef std::ptrdiff_t 								difference_type;
					typedef typename Allocator::pointer 				pointer;
					typedef typename Allocator::const_pointer 			const_pointer;

			private:

					typedef ft::Tree<value_type, key_type, _select_first<value_type>, key_compare, allocator_type>  tree_type;
					typedef typename tree_type::pointer																node_pointer;
			
					tree_type 																						_tree;

			public:

					typedef typename tree_type::iterator				iterator;
					typedef typename tree_type::const_iterator			const_iterator;
					typedef ft::reverse_iterator<iterator> 				reverse_iterator;
					typedef ft::reverse_iterator<const_iterator> 		const_reverse_iterator;
			
				class value_compare : public std::binary_function<value_type,value_type,bool>
				{
					friend class map;

					protected:

						Compare comp;
						value_compare(Compare c) : comp(c) {}

					public:

						bool operator()(const value_type& x, const value_type& y) const
						{
							return comp(x.first, y.first);
						}
				};

			// 23.3.1.1 construct/copy/destroy:
				explicit map(const Compare& comp = Compare(), const Allocator& = Allocator()) : _tree(comp, Allocator()) {}

				template <class InputIterator>
					map(InputIterator first, InputIterator last, const Compare& comp = Compare(), const Allocator& = Allocator()) : _tree(comp, Allocator())
					{
						for (InputIterator it = first; it != last; it++)
						{
							this->insert(*it);
						}
					}
				
				map(const map<Key,T,Compare,Allocator>& x) : _tree(NULL)
				{
					*this = x;
				}

				~map() {}
				
				map<Key,T,Compare,Allocator>& 	operator=(const map<Key,T,Compare,Allocator>& x)
				{
					this->_tree = x._tree;
					return *this;
				}
			
			// iterators:
				iterator 						begin()
				{
					return this->_tree.begin();
				}

				const_iterator 					begin() const
				{
					return this->_tree.begin();
				}

				iterator 						end()
				{
					return this->_tree.end();
				}

				const_iterator 					end() const
				{
					return this->_tree.end();
				}

				reverse_iterator 				rbegin()
				{
					return this->_tree.rbegin();
				}

				const_reverse_iterator 			rbegin() const
				{
					return this->_tree.rbegin();
				}

				reverse_iterator 				rend()
				{
					return this->_tree.rend();
				}

				const_reverse_iterator 			rend() const
				{
					return this->_tree.rend();
				}
			
			// capacity:
				bool 							empty() const
				{
					return (this->size() == 0);
				}

				size_type 						size() const
				{
					return (this->_tree.size());
				}

				size_type 						max_size() const
				{
					return this->_tree.get_allocator_node().max_size();
				}
			
			// 23.3.1.2 element access:
				T& operator[](const key_type& k)
				{
					return (*((this->insert(ft::make_pair(k,mapped_type()))).first)).second;
				}

			// modifiers:
				pair<iterator, bool> 			insert(const value_type& x)
				{
					iterator node = this->_tree.findKeyPositionInTree(x.first);
					if (node != this->end())
						return ft::make_pair(node, false);
					node = this->_tree.insert(x);
					return ft::make_pair(node, true);
				}

				iterator 						insert(iterator position, const value_type& x);
				
				template <class InputIterator>
					void 						insert(InputIterator first, InputIterator last)
					{
						for (InputIterator it = first; it != last; it++)
						{
							this->insert(*it);
						}
					}
				
				void 							erase(iterator position)
				{
					this->_tree.calldeleteNode(position->first);
				}

				size_type 						erase(const key_type& x)
				{
					size_type init_size = this->size();
					this->_tree.calldeleteNode(x);
					return init_size - this->size();
				}

				void 							erase(iterator first, iterator last)
				{
					size_type n = std::distance(first, last);
					iterator tab[n];
					unsigned int i = 0;
					for (iterator it = first; it != last; it++)
						tab[i++] = it;
					for (i = 0; i < n; i++)
						erase(tab[i]);
				}

				void 							swap(map<Key,T,Compare,Allocator>& x)
				{
					this->_tree.swap(x._tree);
				}

				void 							clear()
				{
					if (this->empty())
						return ;
					erase(this->begin(), this->end());
				}

			// observers:
				key_compare key_comp() const
				{
					return this->_tree.get_compare();
				}

				value_compare value_comp() const
				{
					return value_compare(key_compare());
				}

			// 23.3.1.3 map operations:

				iterator 							find(const key_type& x)
				{
					return (this->_tree.findKeyPositionInTree(x));
				}

				const_iterator 						find(const key_type& x) const
				{
					return (this->_tree.findKeyPositionInTreeConst(x));
				}

				size_type 							count(const key_type& x) const
				{
					return this->_tree.findKeyInTree(x) != NULL ? 1 : 0;
				}

				iterator 							lower_bound(const key_type& x)
				{
					iterator ret = this->_tree.lower_bound(x);
					return ret;
				}

				const_iterator 						lower_bound(const key_type& x) const
				{
					const_iterator ret = this->_tree.lower_bound(x);
					return ret;
				}

				iterator 							upper_bound(const key_type& x)
				{
					return this->_tree.upper_bound(x);
				}

				const_iterator 						upper_bound(const key_type& x) const
				{
					return this->_tree.upper_bound(x);
				}

				pair<iterator,iterator>				equal_range(const key_type& x)
				{
					return this->_tree.equal_range(x);
				}

				pair<const_iterator,const_iterator>	equal_range(const key_type& x) const
				{
					return this->_tree.equal_range(x);
				}

				allocator_type get_allocator() const
				{
					return this->_tree.get_allocator_type();
				}

				friend bool operator==(const map<Key,T,Compare,Allocator>& x, const map<Key,T,Compare,Allocator>& y)
				{
					return x._tree == y._tree;
				}

				friend bool operator<(const map<Key,T,Compare,Allocator>& x, const map<Key,T,Compare,Allocator>& y)
				{
					return x._tree < y._tree;
				}

				friend bool operator!=(const map<Key,T,Compare,Allocator>& x, const map<Key,T,Compare,Allocator>& y)
				{
					return !(x == y);
				}

				friend bool operator>(const map<Key,T,Compare,Allocator>& x, const map<Key,T,Compare,Allocator>& y)
				{
					return (y < x);
				}

				friend bool operator>=(const map<Key,T,Compare,Allocator>& x, const map<Key,T,Compare,Allocator>& y)
				{
					return !(x < y);
				}

				friend bool operator<=(const map<Key,T,Compare,Allocator>& x, const map<Key,T,Compare,Allocator>& y)
				{
					return !(y < x);
				}

				friend void swap(map<Key,T,Compare,Allocator>& x, map<Key,T,Compare,Allocator>& y)
				{
					x.swap(y);
				}

		};

};
