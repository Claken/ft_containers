#pragma once

#include <iostream>

namespace ft
{
	template <bool Cond, class T = void>
	struct enable_if
	{

	};


	template <class T>
	struct is_integral
	{

	};
	
	template <class T1, class T2>
	pair<T1,T2>;

	template <class T1, class T2>
	make_pair (T1 x, T2 y);
};
