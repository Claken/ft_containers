// map::value_comp
#include <iostream>
#include <map>
#include "../map.hpp"

#define TESTED_NS std

int main ()
{
  TESTED_NS::map<char,int> mymap;

  mymap['x']=1001;
  mymap['y']=2002;
  mymap['z']=3003;

  std::cout << "mymap contains:\n";

  TESTED_NS::pair<char,int> highest = *mymap.rbegin();          // last element

  TESTED_NS::map<char,int>::iterator it = mymap.begin();
  do {
    std::cout << it->first << " => " << it->second << '\n';
  } while ( mymap.value_comp()(*it++, highest) );

  return 0;
}