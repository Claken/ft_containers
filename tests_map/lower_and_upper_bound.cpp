// map::lower_bound/upper_bound
#include <iostream>
#include <map>
#include "../map.hpp"

#define TESTED_NS ft

int main ()
{
  TESTED_NS::map<char,int> mymap;
  TESTED_NS::map<char,int>::iterator itlow,itup;

  mymap['a']=20;
  mymap['b']=40;
  mymap['c']=60;
  mymap['d']=80;
  mymap['e']=100;

  itlow=mymap.lower_bound ('b');  // itlow points to b
  itup=mymap.upper_bound ('d');   // itup points to e (not d!)

  std::cout << "lower bound == " << itlow->first << std::endl;
  std::cout << "upper bound == " << itup->first << std::endl;

  mymap.erase(itlow,itup);        // erases [itlow,itup)

  // print content:
  for (TESTED_NS::map<char,int>::iterator it=mymap.begin(); it!=mymap.end(); ++it)
    std::cout << it->first << " => " << it->second << '\n';

  return 0;
}