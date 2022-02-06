#pragma once

#include <iostream>
#include <deque>

namespace ft
{
	template <class T, class Container = std::deque<T> >
	class stack 
	{
		protected:
		
			Container c;

		public:
	
			typedef typename Container::value_type 		value_type;
			typedef typename Container::size_type 		size_type;
			typedef Container 							container_type;

			explicit stack(const container_type& ctnr = container_type())
			{
				this->c = ctnr;
			}

			bool empty() const 
			{ 
				return c.empty(); 
			}
			size_type size() const 
			{ 
				return c.size();
			}
			value_type& top() 
			{ 
				return c.back(); 
			}
			const value_type& top() const
			{ 
				return c.back(); 
			}
			void push(const value_type& x)
			{ 
				c.push_back(x); 
			}
			void pop() 
			{ 
				c.pop_back(); 
			}
			
			friend bool operator==(const stack<T, Container> & x, const stack<T, Container> & y)
			{
				typename std::stack<T>::container_type::const_iterator itx = x.c.begin();
				typename std::stack<T>::container_type::const_iterator ity = y.c.begin();
				typename std::stack<T>::container_type::const_iterator itxe = x.c.end();
				typename std::stack<T>::container_type::const_iterator itye = y.c.end();

				while (itx != itxe && ity != itye)
				{
					if (*itx != *ity)
						return (false);
					itx++;
					ity++;
				}
				return (true);
			}
			
			friend bool operator<(const stack<T, Container>& x, const stack<T, Container>& y)
			{
				typename std::stack<T>::container_type::const_iterator itx = x.c.begin();
				typename std::stack<T>::container_type::const_iterator ity = y.c.begin();
				typename std::stack<T>::container_type::const_iterator itxe = x.c.end();
				typename std::stack<T>::container_type::const_iterator itye = y.c.end();

				while (itx != itxe && ity != itye)
				{
					if (*itx < *ity)
						return (true);
					itx++;
					ity++;
				}
				return (false);
			}

			friend bool operator!=(const stack<T, Container>& x, const stack<T, Container>& y)
			{
				typename std::stack<T>::container_type::const_iterator itx = x.c.begin();
				typename std::stack<T>::container_type::const_iterator ity = y.c.begin();
				typename std::stack<T>::container_type::const_iterator itxe = x.c.end();
				typename std::stack<T>::container_type::const_iterator itye = y.c.end();

				while (itx != itxe && ity != itye)
				{
					if (*itx != *ity)
						return (true);
					itx++;
					ity++;
				}
				return (false);
			}

			friend bool operator>(const stack<T, Container>& x, const stack<T, Container>& y)
			{
				typename std::stack<T>::container_type::const_iterator itx = x.c.begin();
				typename std::stack<T>::container_type::const_iterator ity = y.c.begin();
				typename std::stack<T>::container_type::const_iterator itxe = x.c.end();
				typename std::stack<T>::container_type::const_iterator itye = y.c.end();

				while (itx != itxe && ity != itye)
				{
					if (*itx > *ity)
						return (true);
					itx++;
					ity++;
				}
				return (false);
			}

			friend bool operator>=(const stack<T, Container>& x, const stack<T, Container>& y)
			{
				typename std::stack<T>::container_type::const_iterator itx = x.c.begin();
				typename std::stack<T>::container_type::const_iterator ity = y.c.begin();
				typename std::stack<T>::container_type::const_iterator itxe = x.c.end();
				typename std::stack<T>::container_type::const_iterator itye = y.c.end();

				while (itx != itxe && ity != itye)
				{
					if (*itx < *ity)
						return (false);
					itx++;
					ity++;
				}
				return (true);
			}

			friend bool operator<=(const stack<T, Container>& x, const stack<T, Container>& y)
			{
				typename std::stack<T>::container_type::const_iterator itx = x.c.begin();
				typename std::stack<T>::container_type::const_iterator ity = y.c.begin();
				typename std::stack<T>::container_type::const_iterator itxe = x.c.end();
				typename std::stack<T>::container_type::const_iterator itye = y.c.end();

				while (itx != itxe && ity != itye)
				{
					if (*itx > *ity)
						return (false);
					itx++;
					ity++;
				}
				return (true);
			}
	};
	
};
