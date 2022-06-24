#include <iostream>
#include "vector.hpp"
#include <vector>
#include <map>

int main()
{
/*
	ft::vector<int> a(12, 100);
	ft::vector<int> b(5, 200);
	std::cout << "A_size=" << a.size() << " A_cap=" << a.capacity() << " B_size=" << b.size() << " B_cap=" << b.capacity() << std::endl;
	b.resize(5);
	a.resize(5);
	std::cout << "A_size=" << a.size() << " A_cap=" << a.capacity() << " B_size=" << b.size() << " B_cap=" << b.capacity() << std::endl;
	b.resize(12);
	a.resize(12);
	std::cout << "A_size=" << a.size() << " A_cap=" << a.capacity() << " B_size=" << b.size() << " B_cap=" << b.capacity() << std::endl;
	b.resize(10);
	a.resize(10);
	std::cout << "A_size=" << a.size() << " A_cap=" << a.capacity() << " B_size=" << b.size() << " B_cap=" << b.capacity() << std::endl;
	b.at(12);
	a.at(12);
	std::cout << "A_size=" << a.size() << " A_cap=" << a.capacity() << " B_size=" << b.size() << " B_cap=" << b.capacity() << std::endl;
	std::cout << a[1] << " A_size=" << a.size() << " A_cap=" << a.capacity() << " " << b[1] << " B_size=" << b.size() << " B_cap=" << b.capacity() << std::endl;
	a.pop_back();
	std::cout << a[1] << " A_size=" << a.size() << " A_cap=" << a.capacity() << " " << b[1] << " B_size=" << b.size() << " B_cap=" << b.capacity() << std::endl;
	b.swap(a);
	std::cout << a[1] << " A_size=" << a.size() << " A_cap=" << a.capacity() << " " << b[1]  << " B_size=" << b.size() << " B_cap=" << b.capacity() << std::endl;
*/
std::map<std::string, std::vector<int> > map;
std::vector<int> v;
v.push_back(1);
v.push_back(2);
v.push_back(3);
map["one"] = v;

for(const auto &kvp: map) 
{
   std::cout << kvp.first << std::endl;
   for(auto v: kvp.second)
      std::cout << v << std::endl;
}

int arr[] = {1,2,3,4,5};

for(int &e: arr) 
   e *= e;
}