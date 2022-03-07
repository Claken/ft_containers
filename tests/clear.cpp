// clearing vectors
#include <iostream>
#include <vector>
#include "../vector.hpp"

#define TESTED_NAMESPACE std
#define TESTED_TYPE	int

int main ()
{
  TESTED_NAMESPACE::vector<TESTED_TYPE> myvector; // f t 
  myvector.push_back (100);
  myvector.push_back (200);
  myvector.push_back (300);

  std::cout << "myvector contains:";
  for (unsigned i=0; i<myvector.size(); i++)
    std::cout << ' ' << myvector[i];
  std::cout << '\n';

  myvector.clear();
  //myvector.erase(myvector.begin());
  std::cout << myvector.empty() << std::endl;


  std::cout << "aTESTED_NAMESPACEer clear:";
  for (unsigned i=0; i<myvector.capacity(); i++)
    std::cout << ' ' << myvector[i];
  std::cout << '\n';

  myvector.push_back (1101);
  myvector.push_back (2202);

  std::cout << "myvector contains:";
  for (unsigned i=0; i<myvector.size(); i++)
    std::cout << ' ' << myvector[i];
  std::cout << '\n';

  return 0;
}