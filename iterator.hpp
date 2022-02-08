#pragma once

#include <iostream>

namespace ft
{
	template <class Category, class T, class Distance = ptrdiff_t, class Pointer = T*, class Reference = T&>
	struct iterator
	{
		typedef T			value_type;
		typedef Distance	difference_type;
		typedef Pointer		pointer;
		typedef Reference	reference;
		typedef Category	iterator_category;
	};

	template <class Iterator>
	class iterator_traits
	{

	};

	template <class T>
	class iterator_traits<T*>
	{

	};

	template <class T>
	class iterator_traits<const T*>
	{

	};

	template <class Iterator>
	class reverse_iterator
	{

	};
};
