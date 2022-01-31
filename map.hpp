#pragma once

#include <iostream>

namespace ft
{
	template <class Key,
		class T,
		class Compare = std::less<Key>,
		class Allocator = std::allocator<std::pair<const Key, T>>
	class map
	{
		map<Key, T, Compare, Allocator>();
		~map<Key, T, Compare, Allocator>();
	};
};
