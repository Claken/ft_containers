#pragma once

#include <iostream>
#include <new>
#include <cstddef>
#include <algorithm>
#include "iterator.hpp"
#include "utils.hpp"

namespace ft
{
	template <class T>
	class vector_iterator
	{
			public:

			typedef T									value_type;
			typedef std::ptrdiff_t						difference_type;
			typedef T*									pointer;
			typedef T&									reference;
			typedef std::random_access_iterator_tag		iterator_category;

			protected:

				pointer		_ptr;

			public:

				vector_iterator() : _ptr(NULL) {}

				vector_iterator(vector_iterator const &copy) : _ptr(copy._ptr) {}

				explicit vector_iterator(pointer const ptr) : _ptr(ptr) {}

				~vector_iterator() {}

				template<class U>
				vector_iterator(vector_iterator<U> const &copy)
				{
					*this = copy;
				}

				pointer	base() const
				{
					return (this->_ptr);
				}

				reference operator*(void) const
				{
					return (*this->_ptr);
				}

				template<class U>
				vector_iterator& operator=(const vector_iterator<U>& copy)
				{
					this->_ptr = copy.base();
					return (*this);
				}

				vector_iterator& operator=(const vector_iterator& copy)
				{
					this->_ptr = copy.base();
					return (*this);
				}

				vector_iterator& operator++()
				{
					++this->_ptr;
					return (*this);
				}

				vector_iterator operator++(int)
				{
					vector_iterator tmp = *this;
					++this->_ptr;
					return (tmp);
				}

				vector_iterator& operator--()
				{
					--this->_ptr;
					return (*this);
				}

				vector_iterator operator--(int)
				{
					vector_iterator tmp = *this;
					--this->_ptr;
					return (tmp);
				}

				pointer operator->() const
				{
					return &(operator*());
				}

				vector_iterator& operator-=(difference_type n)
				{
					this->_ptr -= n;
					return (*this);
				}

				vector_iterator& operator+=(difference_type n)
				{
					this->_ptr += n;
					return (*this);
				}

				vector_iterator operator-(difference_type n) const
				{
					vector_iterator copy = *this;
					copy._ptr -= n;
					return (copy);
				}

				difference_type operator-(const vector_iterator<T>& instance) const
				{
					return (this->_ptr - instance._ptr);
				}

				template<class U>
				difference_type operator-(const vector_iterator<U>& instance) const
				{
					return (this->_ptr - instance.base());
				}

				vector_iterator operator+(difference_type n) const
				{
					vector_iterator copy = *this;
					copy._ptr += n;
					return (copy);
				}

				difference_type operator+(const vector_iterator<T>& instance) const
				{
					return (this->_ptr + instance._ptr);
				}

				reference operator[] (difference_type n) const
				{
					return (this->_ptr[n]);
				}
		};

		template<class T1, class T2>
		bool operator==(const vector_iterator<T1>& lhs, const vector_iterator<T2>& rhs)
		{
			return (lhs.base() == rhs.base());
		}

		template<class T1, class T2>
		bool operator!=(const vector_iterator<T1>& lhs, const vector_iterator<T2>& rhs)
		{
			return (lhs.base() != rhs.base());
		}

		template<class T1, class T2>
		bool operator<(const vector_iterator<T1>& lhs, const vector_iterator<T2>& rhs)
		{
			return (lhs.base() < rhs.base());
		}
		
		template<class T1, class T2>
		bool operator<=(const vector_iterator<T1>& lhs, const vector_iterator<T2>& rhs)
		{
			return (lhs.base() <= rhs.base());
		}
				
		template<class T1, class T2>
		bool operator>(const vector_iterator<T1>& lhs, const vector_iterator<T2>& rhs)
		{
			return (lhs.base() > rhs.base());
		}

		template<class T1, class T2>
		bool operator>=(const vector_iterator<T1>& lhs, const vector_iterator<T2>& rhs)
		{
			return (lhs.base() >= rhs.base());
		}

		template<class T>
		vector_iterator<T> operator+(typename vector_iterator<T>::difference_type n, const vector_iterator<T>& it)
		{
			return (vector_iterator<T>(it.base() + n));
		}

		template<class T>
		vector_iterator<T> operator-(typename vector_iterator<T>::difference_type n, const vector_iterator<T>& it)
		{
			return (vector_iterator<T>(it.base() - n));
		}

	template <class T, class Allocator = std::allocator<T> >
	class vector
	{
		public:

		// types:
		typedef typename Allocator::reference					reference;
		typedef typename Allocator::const_reference				const_reference;
		typedef typename ft::vector_iterator<T> 				iterator;
		typedef typename ft::vector_iterator<const T> 			const_iterator;
		typedef size_t 											size_type;
		typedef ptrdiff_t 										difference_type;
		typedef T												value_type;
		typedef Allocator										allocator_type;
		typedef typename Allocator::pointer						pointer;
		typedef typename Allocator::const_pointer				const_pointer;
		typedef ft::reverse_iterator<iterator>					reverse_iterator;
		typedef ft::reverse_iterator<const_iterator>			const_reverse_iterator;

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
			for (unsigned int i = 0; i < n; i++)
			{
				this->_allocator_type.construct(this->_array + i, value);
			}
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
				unsigned int i = 0;
				for (InputIterator it1 = first; it1 != last; it1++)
				{
					//this->_array[i++] = *it1;
					this->_allocator_type.construct(this->_array + i++, *it1);
				}
				this->_size = n;
		 	}
	
		vector(const vector& x) : _array(NULL), _size(0), _capacity(0)
		{
			*this = x;
		}

		~vector()
		{
			this->destroy_and_deallocate();
		}

		vector& operator=(const vector& x)
		{
			if (this->_array)
			{
				// this->_allocator_type.deallocate(this->_array, this->_capacity);
				this->destroy_and_deallocate();
			}
			this->_capacity = x._capacity;
			this->_allocator_type = x._allocator_type;
			this->_array = this->try_allocation(this->_capacity);
			this->_size = x._size;
			for (unsigned int i = 0; i < this->_size; i++)
			{
				// this->_array[i] = x._array[i];
				this->_allocator_type.construct(this->_array + i, x._array[i]);
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

		const_iterator				begin() const
		{
			const_iterator it(this->_array + 0);
			return (it);		
		}

		iterator					end()
		{
			iterator it(this->_array + this->_size);
			return (it);
		}

		const_iterator				end() const
		{
			const_iterator it(this->_array + this->_size);
			return (it);
		}

		reverse_iterator			rbegin()
		{
			reverse_iterator rit(this->end());
			return (rit);
		}

		const_reverse_iterator		rbegin() const
		{
			const_reverse_iterator rit(this->end());
			return (rit);
		}

		reverse_iterator			rend()
		{
			reverse_iterator rit(this->begin());
			return (rit);
		}

		const_reverse_iterator		rend() const
		{
			const_reverse_iterator rit(this->begin());
			return (rit);
		}

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
				throw (std::length_error("vector::reserve"));
				//throw (std::length_error("size n is greater than max size"));
			if (n > this->_capacity)
			{
				T* newArray = this->try_allocation(n);
				for (unsigned int i = 0; i < this->_size; i++)
				{
					// newArray[i] = this->_array[i];
					this->_allocator_type.construct(newArray + i, this->_array[i]);
				}
				if (this->_array)
					this->destroy_and_deallocate();
				// this->_allocator_type.deallocate(this->_array, this->_capacity);
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
				unsigned int i = 0;
				while (i < this->_size)
				{
					this->_allocator_type.construct(newArray + i, this->_array[i]);
					i++;
				}
				this->_allocator_type.construct(newArray + i, x);
				if (this->_array)
				{
					this->destroy_and_deallocate();
				}
				this->_array = newArray;
				this->_capacity = newCap;
			}
			else
			{
				this->_allocator_type.construct(this->_array + this->_size, x);
			}
			this->_size++;
		}

		void						pop_back()
		{
			this->erase(this->end() - 1);
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
				// size_type newCap = this->_size == 0 ? 1 : this->_size * 2;
				T* newArray = this->try_allocation(newSize);
				int i = 0;
				ft::vector<T, Allocator>::iterator it = this->begin();
				while (it != position)
				{
					// newArray[i++] = *it;
					this->_allocator_type.construct(newArray + i++, *it);
					it++;
				}
				int j = i + n;
				while (i < j)
				{
					// newArray[i++] = val;
					this->_allocator_type.construct(newArray + i++, val);
				}
				while (it != this->end())
				{
				 	// newArray[i++] = *it;
					this->_allocator_type.construct(newArray + i++, *it);
				 	it++;
				}
				if (this->_array)
					this->destroy_and_deallocate();
				// this->_allocator_type.deallocate(this->_array, this->_capacity);
				this->_array = newArray;
				this->_capacity = newSize;
			}
			else
			{
				if (position == this->end())
				{
					for (unsigned int j = this->_size; j < newSize; j++)
					{
						this->_allocator_type.construct(this->_array + j, val);
					}
				}
				else
				{
					std::cout << "place" << std::endl;
					ft::vector<T, Allocator>::iterator place = this->end() - 1;
					while (place >= position)
					{
						// *(place+n) = *place;
						this->_allocator_type.destroy(&(*(place+n)));
						this->_allocator_type.construct(&(*(place+n)), *place);
						place--;
					}
					for (unsigned int k = 0; k < n; k++)
					{
						place++;
						// *place = val;
						this->_allocator_type.destroy(&(*(place)));
						this->_allocator_type.construct(&(*place), val);
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

		iterator					erase(iterator position) // A TESTER AVEC DES TESTEURS POUR ETRE SUR QUE CA PASSE !
		{
			int pos = find_pos_with_it(position);	
			for (iterator it = position; it + 1 != this->end(); it++)
			{
				// *it = *(it + 1);
				this->_allocator_type.destroy(&(*it));
				this->_allocator_type.construct(&(*it), *(it + 1));
			}
			this->_size--;
			return (this->begin()+pos);
		}

		iterator					erase(iterator first, iterator last) // A TESTER AVEC DES TESTEURS POUR ETRE SUR QUE CA PASSE !
		{
			int pos = find_pos_with_it(first);
			// if (pos == 0 && last == this->end())
			// {
			// 	this->clear();
			// 	return (first);
			// }
			for (iterator it = first; it != last; it++)
			{
				erase(this->begin()+pos);
			}
			if (this->_size == 0)
				return (this->begin());
			return (first);
		}

		void						swap(ft::vector<T, Allocator>& x)
		{
			std::swap(this->_array, x._array);
			std::swap(this->_size, x._size);
			std::swap(this->_capacity, x._capacity);
			std::swap(this->_allocator_type, x._allocator_type);
		}

		void						clear()
		{
			erase(this->begin(), this->end());
		}
			
		friend bool operator==(const vector<T,Allocator>& x, const vector<T,Allocator>& y)
		{
			if (x.size() == y.size())
				return ft::equal(x.begin(), x.end(), y.begin());
			return (false);
		}
		
		friend bool operator<(const vector<T,Allocator>& x, const vector<T,Allocator>& y)
		{
			return ft::lexicographical_compare(x.begin(), x.end(), y.begin(), y.end());
		}
		
		friend bool operator!=(const vector<T,Allocator>& x, const vector<T,Allocator>& y)
		{
			return !(x == y);
		}
		
		friend bool operator> (const vector<T,Allocator>& x, const vector<T,Allocator>& y)
		{
			return (y < x);
		}
		
		friend bool operator>=(const vector<T,Allocator>& x, const vector<T,Allocator>& y)
		{
			return !(x < y);
		}
		
		friend bool operator<=(const vector<T,Allocator>& x, const vector<T,Allocator>& y)
		{
			return !(y < x);
		}

		friend void swap(vector<T,Allocator>& x, vector<T,Allocator>& y)
		{
			std::swap(x._array, y._array);
			std::swap(x._size, y._size);
			std::swap(x._capacity, y._capacity);
			std::swap(x._allocator_type, y._allocator_type);
		}

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

		void destroy_and_deallocate(void)
		{
			for (ft::vector<T, Allocator>::iterator it = this->begin(); it != this->end(); it++)
				this->_allocator_type.destroy(&(*it));
			this->_allocator_type.deallocate(this->_array, this->_capacity);
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