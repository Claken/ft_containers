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

		private:

		T				*_array;
		size_type		_size;
		unsigned int	_capacity;
		Allocator		_allocator_type;

		public:

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
			this->_capacity = n;
			this->_allocator_type = Allocator();
			try
			{
				this->_array = this->_allocator_type.allocate(this->_capacity);
			}
			catch(const std::bad_alloc& ba)
			{
				std::cerr << ba.what() << std::endl;
			}
			for (int i = 0; i < n; i++)
				this->_array[i] = value;
			this->_size = n;
		}
		// template <class InputIterator>
		//  	vector(InputIterator first, InputIterator last, const Allocator& = Allocator())
		//  	{
				 
		//  	}
	
		vector(const vector<T,Allocator>& x) : _array(NULL)
		{
			*this = x;
		}

		~vector()
		{
			this->_allocator_type.deallocate(this->_array, this->_capacity);
		}

		vector<T,Allocator>& operator=(const vector<T,Allocator>& x)
		{
			if (this->_array != NULL)
			{
				this->_allocator_type.deallocate(this->_array, this->_capacity);
			}
			this->_capacity = x._capacity;
			this->_allocator_type = x._allocator_type;
			try
			{
				this->_array = this->_allocator_type.allocate(this->_capacity);
			}
			catch(const std::bad_alloc& ba)
			{
				std::cerr << ba.what() << std::endl;
			}
			this->_size = x._size;
			for (int i = 0; i < this->_size; i++)
				this->_array[i] = x._array[i];
			return (*this);
		}
		//template <class InputIterator>
		//void						assign(InputIterator first, InputIterator last);
		// void						assign(size_type n, const T& u);
		
		allocator_type				get_allocator() const
		{
			return (this->_allocator_type);
		}
	
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
			return (this->_allocator_type.max_size());
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
		void						reserve(size_type n)
		{
			if (n > this->max_size())
				throw (std::length_error("size n is greater than max size"));
			if (n > this->_capacity)
			{
				vector<T, Allocator> newVector(n);
				newVector._size = this->_size;
				newVector._allocator_type = this->_allocator_type;
				for (int i = 0; i < newVector._size; i++)
					newVector._array[i] = this->_array[i];
				*this = newVector;
			}
		}

		// element access:
		reference					operator[](size_type n)
		{
			return (this->_array[n]);
		}

		const_reference				operator[](size_type n) const
		{
			return (this->_array[n]);
		}

		const_reference				at(size_type n) const
		{
			if (n >= this->_size || n < 0)
				throw (std::out_of_range("index n is out of range"));
			return (this->_array[n]);
		}

		reference					at(size_type n)
		{
			if (n >= this->_size || n < 0)
				throw (std::out_of_range("index n is out of range"));
			return (this->_array[n]);
		}

		reference					front()
		{
			return (this->_array[0]);
		}

		const_reference				front() const
		{
			return (this->_array[0]);
		}

		reference					back()
		{
			return (this->_array[this->_size - 1]);
		}

		const_reference				back() const
		{
			return (this->_array[this->_size - 1]);
		}

		// 23.2.4.3 modifiers:
		void						push_back(const T& x)
		{
			if (this->_size + 1 > this->_capacity)
			{
				vector<T, Allocator> newVector(this->_size * 2);
				newVector._size = this->_size + 1;
				newVector._allocator_type = this->_allocator_type;
				for (int i = 0; i < this->_size; i++)
					newVector._array[i] = this->_array[i];
				newVector._array[this->_size] = x;
				*this = newVector;
			}
			else
			{
				this->_array[this->_size] = x;
				this->_size += 1;
			}
		}

		// void						pop_back();
		// iterator					insert(iterator position, const T& x);
		// void						insert(iterator position, size_type n, const T& x);
		// template <class InputIterator>
		// void						insert(iterator position, InputIterator first, InputIterator last);
		// iterator					erase(iterator position);
		// iterator					erase(iterator first, iterator last);
		// void						swap(vector<T,Allocator>&);
		void						clear()
		{
			this->_size = 0;
		}

	// friend bool operator==(const vector<T,Allocator>& x, const vector<T,Allocator>& y);
	// friend bool operator<(const vector<T,Allocator>& x, const vector<T,Allocator>& y);
	// friend bool operator!=(const vector<T,Allocator>& x, const vector<T,Allocator>& y);
	// friend bool operator>(const vector<T,Allocator>& x, const vector<T,Allocator>& y);
	// friend bool operator>=(const vector<T,Allocator>& x, const vector<T,Allocator>& y);
	// friend bool operator<=(const vector<T,Allocator>& x, const vector<T,Allocator>& y);

	// friend void swap(vector<T,Allocator>& x, vector<T,Allocator>& y);
		
	};


};