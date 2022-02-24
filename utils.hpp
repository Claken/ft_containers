#pragma once

#include <iostream>

namespace ft
{
	template <class T, T v>
	struct integral_constant
	{
		public:

		static const T					value = v;
		typedef T						value_type;
		typedef integral_constant<T,v>	type;
		operator value_type() const
		{
			return value;
		}
	};

	// template <class T>
	// struct is_integral : public ft::integral_constant<bool, __is_integral(T)> {};

	template <class T>
	struct is_integral : public ft::integral_constant<bool, false> { };

	template <>
	struct is_integral<bool> : public ft::integral_constant<bool, true> { };
	template <>
	struct is_integral<char> : public ft::integral_constant<bool, true> { };
	template <>
	struct is_integral<wchar_t> : public ft::integral_constant<bool, true> { };
	template <>
	struct is_integral<signed char> : public ft::integral_constant<bool, true> { };
	template <>
	struct is_integral<short int> : public ft::integral_constant<bool, true> { };
	template <>
	struct is_integral<int> : public ft::integral_constant<bool, true> { };
	template <>
	struct is_integral<long int> : public ft::integral_constant<bool, true> { };
	template <>
	struct is_integral<long long int> : public ft::integral_constant<bool, true> { };
	template <>
	struct is_integral<unsigned char> : public ft::integral_constant<bool, true> { };
	template <>
	struct is_integral<unsigned short int> : public ft::integral_constant<bool, true> { };
	template <>
	struct is_integral<unsigned int> : public ft::integral_constant<bool, true> { };
	template <>
	struct is_integral<unsigned long int> : public ft::integral_constant<bool, true> { };
	template <>
	struct is_integral<unsigned long long int> : public ft::integral_constant<bool, true> { };
	

	template<bool Cond, class T = void>
	struct enable_if {};

	template<class T>
	struct enable_if<true, T>
	{
		typedef T type;
	};

	template <class InputIterator1, class InputIterator2>
	bool equal (InputIterator1 first1, InputIterator1 last1, InputIterator2 first2)
	{
		while (first1!=last1)
		{
			if (!(*first1 == *first2))
				return false;
			++first1;
			++first2;
		}
		return true;
	}

	template <class InputIterator1, class InputIterator2, class BinaryPredicate>
	bool equal (InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, BinaryPredicate pred)
	{
		while (first1!=last1)
		{
			if (!(pred(*first1, *first2)))
				return false;
			++first1;
			++first2;
		}
		return true;
	}

	template <class InputIterator1, class InputIterator2>
	bool lexicographical_compare (InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, InputIterator2 last2)
	{
		while (first1!=last1)
		{
			if (first2==last2 || *first2 < *first1)
			{
				return false;
			}
			else if (*first1 < *first2)
			{
				return true;
			}
			++first1;
			++first2;
		}
		return (first2!=last2);
	}

	template <class InputIterator1, class InputIterator2, class Compare>
	bool lexicographical_compare (InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, InputIterator2 last2, Compare comp)
	{
		while (first1!=last1)
		{
			if (first2==last2 || comp(*first2, *first1))
			{
				return false;
			}
			else if (comp(*first1, *first2))
			{
				return true;
			}
			++first1;
			++first2;
		}
		return (first2!=last2);
	}


	template <class T1, class T2>
	struct pair
	{
		typedef T1 first_type;
		typedef T2 second_type;

		public:

		first_type		first;
		second_type		second;

		pair() : first(T1()), second(T2()) {}

		template<class U, class V>
		pair (const pair<U,V>& pr)
		{
			*this = pr;
		}

		pair (const first_type& a, const second_type& b)
		{
			this->first = a;
			this->second = b;
		}

		pair& operator= (const pair& pr)
		{
			this->first = pr.first;
			this->second = pr.second;
			return (*this);
		}

		friend bool operator== (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
		{
			return lhs.first==rhs.first && lhs.second==rhs.second;
		}

		friend bool operator!= (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
		{
			return !(lhs==rhs);
		}

		friend bool operator<  (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
		{
			return lhs.first<rhs.first || (!(rhs.first<lhs.first) && lhs.second<rhs.second);
		}

		friend bool operator<= (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
		{
			return !(rhs<lhs);
		}

		friend bool operator>  (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
		{
			return rhs<lhs;
		}

		friend bool operator>= (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
		{
			return !(lhs<rhs);
		}
	};

	template <class T1, class T2>
	pair<T1,T2>		make_pair(T1 x, T2 y)
	{
		return ( pair<T1,T2>(x,y) );
	}
}
