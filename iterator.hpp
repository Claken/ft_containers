#pragma once

#include <iostream>

namespace ft
{
	template <class Category, class T, class Distance = ptrdiff_t, class Pointer = T*, class Reference = T&>
		struct iterator
		{
			public :

			typedef T										value_type;
			typedef Distance								difference_type;
			typedef Pointer									pointer;
			typedef Reference								reference;
			typedef Category								iterator_category;
		};

	template <class Iterator>
		class iterator_traits
		{
			public :

			typedef typename Iterator::difference_type		difference_type;
			typedef typename Iterator::value_type			value_type;
			typedef typename Iterator::pointer				pointer;
			typedef typename Iterator::reference			reference;
			typedef typename Iterator::iterator_category	iterator_category;
		};

	template <class T>
		class iterator_traits<T*>
		{
			public :

			typedef ptrdiff_t								difference_type;
			typedef T										value_type;
			typedef T*										pointer;
			typedef T&										reference;
			typedef std::random_access_iterator_tag			iterator_category;
		};

	template <class T>
		class iterator_traits<const T*>
		{
			public :
			
			typedef ptrdiff_t								difference_type;
			typedef T										value_type;
			typedef const T*								pointer;
			typedef const T&								reference;
			typedef std::random_access_iterator_tag			iterator_category;
		};

	template <class Iterator>
		class reverse_iterator : public iterator<typename iterator_traits<Iterator>::iterator_category,
		typename iterator_traits<Iterator>::value_type, typename iterator_traits<Iterator>::difference_type,
		typename iterator_traits<Iterator>::pointer, typename iterator_traits<Iterator>::reference>
		{
			protected:

				Iterator current;

			public:

				typedef Iterator 											iterator_type;
				typedef typename iterator_traits<Iterator>::difference_type	difference_type;
				typedef typename iterator_traits<Iterator>::reference		reference;
				typedef typename iterator_traits<Iterator>::pointer			pointer;
				
				reverse_iterator() {}

				explicit reverse_iterator (iterator_type it)
				{
					this->current = it;
				}

				template <class Iter>
					reverse_iterator (const reverse_iterator<Iter>& rev_it)
					{
						this->current = rev_it.base();
					}

				iterator_type base() const
				{
					return (this->current);
				}

				reference operator*() const
				{
					Iterator tmp = this->current;
					--tmp;
					return *tmp;
				}

				reverse_iterator operator+ (difference_type n) const
				{
					return (reverse_iterator(this->current-n));
				}

				reverse_iterator& operator++()
				{
					--this->current;
					return (*this);
				}

				reverse_iterator  operator++(int)
				{
					reverse_iterator tmp = *this;
					--this->current;
					return (tmp);
				}

				reverse_iterator& operator+= (difference_type n)
				{
					this->current -= n;
					return (*this);
				}

				reverse_iterator operator- (difference_type n) const
				{
					return (reverse_iterator(this->current+n));
				}

				reverse_iterator& operator--()
				{
					++this->current;
					return (*this);
				}

				reverse_iterator operator--(int)
				{
					reverse_iterator tmp = *this;
					--this->current;
					return tmp;
				}

				reverse_iterator& operator-= (difference_type n)
				{
					this->current += n;
					return (*this);
				}

				pointer operator->() const
				{
					return &(operator*());
				}

				reference operator[] (difference_type n) const
				{
					return (this->current[-n-1]);
				}
		};
				template<class Iterator1, class Iterator2>
					bool operator== (const reverse_iterator<Iterator1>& lhs, const reverse_iterator<Iterator2>& rhs)
					{
						return (lhs.base() == rhs.base());
					}

				template<class Iterator1, class Iterator2>
					bool operator!= (const reverse_iterator<Iterator1>& lhs, const reverse_iterator<Iterator2>& rhs)
					{
						return (lhs.base() != rhs.base());
					}

				template<class Iterator1, class Iterator2>
					bool operator<  (const reverse_iterator<Iterator1>& lhs, const reverse_iterator<Iterator2>& rhs)
					{
						return (lhs.base() > rhs.base());
					}
				template<class Iterator1, class Iterator2>
					bool operator<= (const reverse_iterator<Iterator1>& lhs, const reverse_iterator<Iterator2>& rhs)
					{
						return (lhs.base() >= rhs.base());
					}
				
				template<class Iterator1, class Iterator2>
					bool operator>  (const reverse_iterator<Iterator1>& lhs, const reverse_iterator<Iterator2>& rhs)
					{
						return (lhs.base() < rhs.base());
					}

				template<class Iterator1, class Iterator2>
					bool operator>= (const reverse_iterator<Iterator1>& lhs, const reverse_iterator<Iterator2>& rhs)
					{
						return (lhs.base() <= rhs.base());
					}

				template<class Iterator>
					reverse_iterator<Iterator> operator+(typename reverse_iterator<Iterator>::difference_type n, const reverse_iterator<Iterator>& rev_it)
					{
						return (reverse_iterator<Iterator>(rev_it.base() - n));
					}

				template<class Iterator>
					typename reverse_iterator<Iterator>::difference_type operator-(const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs)
					{
						return (rhs.base() - lhs.base());
					}

				template<class Iterator1, class Iterator2>
					typename reverse_iterator<Iterator1>::difference_type operator-(const reverse_iterator<Iterator1>& lhs, const reverse_iterator<Iterator2>& rhs)
					{
						return (rhs.base() - lhs.base());
					}
};
