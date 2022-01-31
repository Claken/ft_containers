#pragma once

#include <iostream>

namespace ft
{
	template<class T, class Allocator = std::allocator<T>>
	class vector
	{
		vector<T, Allocator>();
		~vector<T, Allocator>();
	};
};
