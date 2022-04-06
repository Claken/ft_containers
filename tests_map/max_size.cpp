// map::max_size
#include <iostream>
#include <map>
#include "../map.hpp"

#define NAME_SP std

int main ()
{
  int i;
  NAME_SP::map<int,int> mymap;

  std::cout << mymap.max_size() << std::endl;

  if (mymap.max_size()>1000)
  {
    for (i=0; i<1000; i++)
        mymap[i]=0;
    std::cout << "The map contains 1000 elements.\n";
  }
  else
    std::cout << "The map could not hold 1000 elements.\n";

  return 0;
}