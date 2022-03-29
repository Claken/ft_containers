// map::equal_range
#include <iostream>
#include <map>
#include "../map.hpp"

#define TESTED_NS ft

int main ()
{
  TESTED_NS::map<char,int> mymap;

  mymap['a']=10;
  mymap['b']=20;
  mymap['c']=30;

  TESTED_NS::pair<TESTED_NS::map<char,int>::iterator,TESTED_NS::map<char,int>::iterator> ret;
  ret = mymap.equal_range('b');

  std::cout << "lower bound points to: ";
  std::cout << ret.first->first << " => " << ret.first->second << '\n';

  std::cout << "upper bound points to: ";
  std::cout << ret.second->first << " => " << ret.second->second << '\n';

  return 0;
}