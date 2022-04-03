/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_main.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbaudet <hbaudet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/02 13:07:06 by hbaudet           #+#    #+#             */
/*   Updated: 2021/01/18 16:05:27 by hbaudet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <map>
#include "../map.hpp"

# define NAMESPACE std

using namespace NAMESPACE;

template <class Key, class T>
void	print(map<Key, T>& lst)
{
	for (typename map<Key, T>::iterator it = lst.begin(); it != lst.end(); it++)
		std::cout << it->first << " => " << it->second << '\n';
}

int main ()
{
  map<char,int> mymap;
  char c;

  mymap ['a']=101;
  std::cout << "assigned 'a'\n";
  mymap ['c']=202;
  std::cout << "assiged 'c'\n";
  mymap ['f']=303;
  std::cout << "assigned 'f'\n";

	std::cout << "end of assignations\n";
  for (c='a'; c<'h'; c++)
  {
    std::cout << c;
    if (mymap.count(c)>0)
      std::cout << " is an element of mymap.\n";
    else 
      std::cout << " is not an element of mymap.\n";
  }

  return 0;
}
