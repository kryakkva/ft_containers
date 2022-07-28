#include <map>
#include <iostream>
#include <list>
#include "../map.hpp"

#define NAMESPACE ft
using namespace NAMESPACE;
int main(void)
{
	NAMESPACE::map<std::string, char> mymap;
	// NAMESPACE::map<std::string, std::string> mymap;
  std::cout << mymap.max_size() << std::endl;


  return 0;
}