#pragma once

#include <iostream>
#include <new>
#include <cstddef>
#include "iterator.hpp"

namespace ft
{
	template <class T, class Allocator = std::allocator<T> >
	class vector
	{
		private:

		T				*_array;
		unsigned int	_size;
		unsigned int	_capacity;
		Allocator		_allocator_type;

		public:
	
		// types:
		typedef typename Allocator::reference				reference;
		typedef typename Allocator::const_reference			const_reference;
		//typedef implementation defined iterator; // See 23.1
		//typedef implementation defined const_iterator; // See 23.1
		typedef size_t 										size_type; // See 23.1
		typedef ptrdiff_t 									difference_type;// See 23.1
		typedef T											value_type;
		typedef Allocator									allocator_type;
		typedef typename Allocator::pointer					pointer;
		typedef typename Allocator::const_pointer			const_pointer;
		//typedef std::reverse_iterator<const_iterator>		const_reverse_iterator;

		class iterator : public ft::iterator<std::forward_iterator_tag, T>
		{
			private:

				pointer		_ptr;

			public:

				iterator() : _ptr(NULL) {}

				iterator(iterator const & copy)
				{
					*this = copy;
				}

				iterator(pointer ptr)
				{
					this->_ptr = ptr;
				}

				reference operator*() const
				{
					return *(this->_ptr);
				}

				iterator& operator=(iterator const & copy)
				{
					this->_ptr = copy._ptr;
					return (*this);
				}

				iterator& operator++()
				{
					++_ptr;
					return (*this);
				}

				iterator& operator++(int)
				{
					iterator tmp = *this;
					++_ptr;
					return (tmp);
				}

				iterator& operator--()
				{
					--_ptr;
					return (*this);
				}

				iterator& operator--(int)
				{
					iterator tmp = *this;
					--_ptr;
					return (tmp);
				}

				pointer operator->() const
				{
					return &(operator*());
				}

				iterator& operator-=(difference_type n)
				{
					this->_ptr -= n;
					return (*this);
				}

				iterator& operator+=(difference_type n)
				{
					this->_ptr += n;
					return (*this);
				}

				iterator operator-(difference_type n) const
				{
					iterator copy = *this;
					copy._ptr -= n;
					return (copy);
				}

				iterator operator+(difference_type n) const
				{
					iterator copy = *this;
					copy._ptr += n;
					return (copy);
				}

				reference operator[] (difference_type n) const
				{
					return (this->_ptr + n);
				}
		};

		typedef std::reverse_iterator<iterator>				reverse_iterator;

		// 23.2.4.1 construct/copy/destroy:
		explicit vector(const Allocator& = Allocator())
		{
			this->_array = NULL;
			this->_size = 0;
			this->_capacity = 0;
			this->_allocator_type = Allocator();
		}

		explicit vector(size_type n, const T& value = T(), const Allocator& = Allocator())
		{
			this->_allocator_type = Allocator();
			try
			{
				this->_array = this->_allocator_type.allocate(n);
			}
			catch(const std::bad_alloc& ba)
			{
				std::cerr << ba.what() << std::endl;
			}
			for (int i = 0; i < n; i++)
				this->_array[i] = value;
			this->_size = n;
			
		}
		//template <class InputIterator>
		//vector(InputIterator first, InputIterator last, const Allocator& = Allocator());
		//vector(const vector<T,Allocator>& x);

		~vector()
		{
			Allocator().deallocate(this->_array, this->_capacity);
		}

		//vector<T,Allocator>& operator=(const vector<T,Allocator>& x);
		//template <class InputIterator>
		//void						assign(InputIterator first, InputIterator last);
		//void						assign(size_type n, const T& u);
		//allocator_type				get_allocator() const;
	
		// iterators:
		iterator					begin()
		{
			iterator it(this->_array + 0);
			return (it);
		}

		//const_iterator				begin() const;

		iterator					end()
		{
			iterator it(this->_array + this->_size);
			return (it);
		}

		//const_iterator				end() const;

		// reverse_iterator			rbegin()
		// {

		// }

		// const_reverse_iterator		rbegin() const
		// {

		// }

		// reverse_iterator			rend()
		// {
			
		// }

		// const_reverse_iterator		rend() const
		// {

		// }

		// 23.2.4.2 capacity:
		size_type					size() const
		{
			return (this->_size);
		}

		size_type					max_size() const
		{
			return (Allocator().max_size());
		}
		//void						resize(size_type sz, T c = T());
		size_type					capacity() const
		{
			return (this->_capacity);
		}
		
		bool						empty() const
		{
			if (this->_size == 0)
				return (true);
			return (false);
		}
		//void						reserve(size_type n);

		// element access:
		// reference					operator[](size_type n);
		// const_reference				operator[](size_type n) const;
		// const_reference				at(size_type n) const;
		// reference					at(size_type n);
		// reference					front();
		// const_reference				front() const;
		// reference					back();
		// const_reference				back() const;

		// 23.2.4.3 modifiers:
		// void						push_back(const T& x);
		// void						pop_back();
		// iterator					insert(iterator position, const T& x);
		// void						insert(iterator position, size_type n, const T& x);
		// template <class InputIterator>
		// void						insert(iterator position, InputIterator first, InputIterator last);
		// iterator					erase(iterator position);
		// iterator					erase(iterator first, iterator last);
		// void						swap(vector<T,Allocator>&);
		// void						clear();

	// friend bool operator==(const vector<T,Allocator>& x, const vector<T,Allocator>& y);
	// friend bool operator<(const vector<T,Allocator>& x, const vector<T,Allocator>& y);
	// friend bool operator!=(const vector<T,Allocator>& x, const vector<T,Allocator>& y);
	// friend bool operator>(const vector<T,Allocator>& x, const vector<T,Allocator>& y);
	// friend bool operator>=(const vector<T,Allocator>& x, const vector<T,Allocator>& y);
	// friend bool operator<=(const vector<T,Allocator>& x, const vector<T,Allocator>& y);

	// friend void swap(vector<T,Allocator>& x, vector<T,Allocator>& y);

	};


};