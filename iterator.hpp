#pragma once

#include <iostream>

namespace ft
{
	template <class Category, class T, class Distance = ptrdiff_t, class Pointer = T*, class Reference = T&>
		struct iterator
		{
			typedef T								value_type;
			typedef Distance						difference_type;
			typedef Pointer							pointer;
			typedef Reference						reference;
			typedef Category						iterator_category;
		};

	template <class Iterator>
		class iterator_traits
		{
			typedef Iterator::difference_type		difference_type;
			typedef Iterator::value_type			value_type;
			typedef Iterator::pointer				pointer;
			typedef Iterator::reference				reference;
			typedef Iterator::iterator_category		iterator_category;
		};

	template <class T>
		class iterator_traits<T*>
		{
			typedef ptrdiff_t						difference_type;
			typedef T								value_type;
			typedef T*								pointer;
			typedef T&								reference;
			typedef random_access_iterator_tag		iterator_category;
		};

	template <class T>
		class iterator_traits<const T*>
		{
			typedef ptrdiff_t						difference_type;
			typedef T								value_type;
			typedef const T*						pointer;
			typedef const T&						reference;
			typedef random_access_iterator_tag		iterator_category;
		};

	template <class Iterator>
		class reverse_iterator
		{
			private:

			public:

				reverse_iterator()
				{

				}

				explicit reverse_iterator (iterator_type it)
				{

				}

				template <class Iter>
					reverse_iterator (const reverse_iterator<Iter>& rev_it)
					{

					}

				iterator_type base() const
				{

				}

				reference operator*() const
				{

				}

				reverse_iterator operator+ (difference_type n) const
				{

				}

				reverse_iterator& operator++()
				{

				}

				reverse_iterator  operator++(int)
				{

				}

				reverse_iterator& operator+= (difference_type n)
				{

				}

				reverse_iterator operator- (difference_type n) const
				{

				}

				reverse_iterator& operator--()
				{

				}

				reverse_iterator operator--(int)
				{

				}

				reverse_iterator& operator-= (difference_type n)
				{

				}

				pointer operator->() const
				{
					return &(operator*());
				}

				reference operator[] (difference_type n) const;

				friend bool operator== (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs);

				friend bool operator!= (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs);

				friend bool operator<  (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs);

				friend bool operator<= (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs);

				friend bool operator>  (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs);

				friend bool operator>= (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs);

				friend reverse_iterator<Iterator> operator+ (typename reverse_iterator<Iterator>::difference_type n, const reverse_iterator<Iterator>& rev_it);

				friend typename reverse_iterator<Iterator>::difference_type operator- (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs);

		};
};
