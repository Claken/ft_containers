#pragma once

#include <iostream>
#include <new>
#include <cstddef>
#include "iterator.hpp"
#include "utils.hpp"

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

		public:

		class iterator : public ft::iterator<std::forward_iterator_tag, T>
		{
			protected:

				pointer		_ptr;

			public:

				iterator() : _ptr(NULL) {}

				iterator(iterator const & copy)
				{
					*this = copy;
				}

				explicit iterator(pointer const ptr)
				{
					this->_ptr = ptr;
				}

				pointer	base() const
				{
					return (this->_ptr);
				}

				reference operator*(void) const
				{
					return (*this->_ptr);
				}

				iterator& operator=(iterator const & copy)
				{
					this->_ptr = copy._ptr;
					return (*this);
				}

				iterator& operator++()
				{
					++this->_ptr;
					return (*this);
				}

				iterator operator++(int)
				{
					iterator tmp = *this;
					++this->_ptr;
					return (tmp);
				}

				iterator& operator--()
				{
					--this->_ptr;
					return (*this);
				}

				iterator operator--(int)
				{
					iterator tmp = *this;
					--this->_ptr;
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

				bool operator==(const iterator it)
				{
					return (this->_ptr == it._ptr);
				}

				bool operator<(const iterator it)
				{
					return (this->_ptr < it._ptr);
				}

				bool operator!=(const iterator it)
				{
					return (this->_ptr != it._ptr);
				}

				bool operator>(const iterator it)
				{
					return (this->_ptr > it._ptr);
				}

				bool operator>=(const iterator it)
				{
					return (this->_ptr >= it._ptr);
				}

				bool operator<=(const iterator it)
				{
					return (this->_ptr <= it._ptr);
				}
				
		};

		typedef ft::reverse_iterator<iterator>				reverse_iterator;

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
			this->_array = this->try_allocation(this->_capacity);
			for (int i = 0; i < n; i++)
				this->_array[i] = value;
			this->_size = n;
		}

		template <class InputIterator>
		 	vector(InputIterator first, InputIterator last, const Allocator& = Allocator(),
			typename ft::enable_if<!ft::is_integral<InputIterator>::value >::type* = NULL)
		 	{
				size_type n = 0;
				for (InputIterator it = first; it != last; it++)
					n++;
				this->_capacity = n;
				this->_allocator_type = Allocator();
				this->_array = this->try_allocation(this->_capacity);
				int i = 0;
				for (InputIterator it1 = first; it1 != last; it1++)
				{
					this->_array[i++] = *it1;
				}
				this->_size = n;
		 	}
	
		vector(const iterator& x) : _array(NULL)
		{
			*this = x;
		}

		~vector()
		{
			this->_allocator_type.deallocate(this->_array, this->_capacity);
		}

		iterator& operator=(const iterator& x)
		{
			if (this->_array != NULL)
			{
				this->_allocator_type.deallocate(this->_array, this->_capacity);
			}
			this->_capacity = x._capacity;
			this->_allocator_type = x._allocator_type;
			this->_array = this->try_allocation(this->_capacity);
			this->_size = x._size;
			for (int i = 0; i < this->_size; i++)
			{
				this->_array[i] = x._array[i];
			}
			return (*this);
		}
		
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

		reverse_iterator			rbegin()
		{
			reverse_iterator rit(this->end());
			return (rit);
		}

		// const_reverse_iterator		rbegin() const
		// {
		// 	return (this->end() - 1);
		// }

		reverse_iterator			rend()
		{
			reverse_iterator rit(this->begin());
			return (rit);
		}

		// const_reverse_iterator		rend() const
		// {
		// 	return (this->begin());
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

		void						resize(size_type sz, T c = T())
		{
			if (sz < this->_size)
			{
				this->_size = sz;
			}
			else if (sz > this->_size)
			{
				this->insert(this->end(), sz - this->_size, c);
			}
		}

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
				T* newArray = this->try_allocation(n);
				for (int i = 0; i < this->_size; i++)
				{
					newArray[i] = this->_array[i];
				}
				if (this->_array)
					this->_allocator_type.deallocate(this->_array, this->_capacity);
				this->_array = newArray;
				this->_capacity = n;
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
				size_type newCap = this->_size == 0 ? 1 : this->_size * 2;
				T* newArray = this->try_allocation(newCap);
				int i = -1;
				while (++i < this->_size)
					newArray[i] = this->_array[i];
				newArray[i] = x;
				if (this->_array)
					this->_allocator_type.deallocate(this->_array, this->_capacity);
				this->_array = newArray;
				this->_capacity = newCap;
			}
			else
			{
				this->_array[this->_size] = x;
			}
			this->_size++;
		}

		void						pop_back()
		{
			if (this->_size > 0)
				this->_size--;
		}

		template <class InputIterator>
  		void 						assign (InputIterator first, InputIterator last,
									typename ft::enable_if<!ft::is_integral<InputIterator>::value >::type* = NULL)
		{
			this->clear();
			this->insert(this->begin(), first, last);
		}

		void 						assign (size_type n, const value_type& val)
		{
			this->clear();
			this->insert(this->begin(), n, val);
		}

		void 						insert (iterator position, size_type n, const value_type& val)
		{
			size_type newSize = n + this->_size;
			if (newSize > this->_capacity)
			{
				T* newArray = this->try_allocation(newSize);
				int i = 0;
				ft::vector<T, Allocator>::iterator it = this->begin();
				while (it != position)
				{
					newArray[i++] = *it;
					it++;
				}
				int j = i + n;
				while (i < j)
				{
					newArray[i++] = val;
				}
				while (it != this->end())
				{
				 	newArray[i++] = *it;
				 	it++;
				}
				if (this->_array)
					this->_allocator_type.deallocate(this->_array, this->_capacity);
				this->_array = newArray;
				this->_capacity = newSize;
			}
			else
			{
				if (position == this->end())
				{
					for (int j = this->_size; j < newSize; j++)
					{
						this->_array[j] = val;
					}
				}
				else
				{
					ft::vector<T, Allocator>::iterator place = this->end() - 1;
					while (place >= position)
					{
						*(place+n) = *place;
						place--;
					}
					for (int k = 0; k < n; k++)
					{
						place++;
						*place = val;
					}
				}
			}
			this->_size = newSize;
		}

		iterator 					insert (iterator position, const value_type& val)
		{
			int pos = find_pos_with_it(position);
			this->insert(position, 1, val);
			return (this->begin()+pos);
		}

		template <class InputIterator>
    		void 					insert (iterator position, InputIterator first, InputIterator last,
									typename ft::enable_if<!ft::is_integral<InputIterator>::value >::type* = NULL)
			{
				int pos = find_pos_with_it(position);
				for (InputIterator it = first; it != last; it++)
				{
					insert(this->begin()+pos, 1, *it);
					pos++;
				}
			}

		iterator					erase(iterator position)
		{
			int pos = find_pos_with_it(position);	
			for (iterator it = position; it + 1 != this->end(); it++)
			{
				*it = *(it + 1);
			}
			this->_size--;
			return (this->begin()+pos);
		}

		iterator					erase(iterator first, iterator last)
		{
			int pos = find_pos_with_it(first);
			for (iterator it = first; it != last; it++)
			{
				erase(this->begin()+pos);
			}
			return (first);
		}

		// void						swap(iterator&);

		void						clear()
		{
			this->_size = 0;
		}
		
	// friend bool operator==(const vector<T,Allocator>& x, const vector<T,Allocator>& y);
	
	// friend bool operator< (const vector<T,Allocator>& x, const vector<T,Allocator>& y);
	
	// friend bool operator!=(const vector<T,Allocator>& x, const vector<T,Allocator>& y);
	
	// friend bool operator> (const vector<T,Allocator>& x, const vector<T,Allocator>& y);
	
	// friend bool operator>=(const vector<T,Allocator>& x, const vector<T,Allocator>& y);
	
	// friend bool operator<=(const vector<T,Allocator>& x, const vector<T,Allocator>& y);

	// friend void swap(vector<T,Allocator>& x, vector<T,Allocator>& y);

		private:

		T				*_array;
		size_type		_size;
		size_type		_capacity;
		Allocator		_allocator_type;
		
		T* try_allocation(size_type n)
		{
			T* newArray;
			try
			{
				newArray = this->_allocator_type.allocate(n);
			}
			catch(const std::bad_alloc& ba)
			{
				std::cerr << ba.what() << std::endl;
			}
			return (newArray);
		}

		int find_pos_with_it(iterator position)
		{
			int pos = 0;
			ft::vector<T, Allocator>::iterator it = this->begin();
			while (it != position)
			{
				pos++;
				it++;
			}
			return (pos);
		}
		
	};


};