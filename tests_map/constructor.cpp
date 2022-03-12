// constructing maps
#include <iostream>
#include <map>

bool fncomp (char lhs, char rhs) {return lhs<rhs;}

struct classcomp {
	bool operator() (const char& lhs, const char& rhs) const
	{return lhs<rhs;}
};

int main ()
{
	std::map<char,int> caca;

	caca['a']=10;
	caca['b']=15;
	caca['c']=20;
	caca['d']=25;

	for (std::map<char,int>::iterator it = caca.begin(); it != caca.end(); it++)
	{
		std::cout << "it->first  = " << it->first << std::endl;
		std::cout << "it->second = " << it->second << std::endl;
		std::cout << std::endl;
	}

	//   std::map<char,int> second (first.begin(),first.end());

	//   std::map<char,int> third (second);

	//   std::map<char,int,classcomp> fourth;                 // class as Compare

	//   bool(*fn_pt)(char,char) = fncomp;
	//   std::map<char,int,bool(*)(char,char)> fifth (fn_pt); // function pointer as Compare

	return 0;
}