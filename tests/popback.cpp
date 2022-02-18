// vector::pop_back
#include <iostream>
#include <vector>
#include "../vector.hpp"

int main ()
{
  ft::vector<int> myvector;
  int sum (0);
  myvector.push_back (100);
  myvector.push_back (200);
  myvector.push_back (300);

  while (!myvector.empty())
  {
    sum+=myvector.back();
    myvector.pop_back();
  }
//   int i = -1;
//   while (++i < myvector.size())
//   {
//       std::cout << myvector[i] << std::endl;
//   }

  std::cout << "The elements of myvector add up to " << sum << '\n';

  return 0;
}