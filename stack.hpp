#pragma once

#include <iostream>
#include <deque>

namespace ft
{
	template <class T, class Container = deque<T>>
	class stack
	{
		stack<T, Container>();
		~stack<T, Container>();
	};
};
