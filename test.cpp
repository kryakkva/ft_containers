#include <iostream>
#include "vector.hpp"
#include <vector>

int main()
{
	ft::vector<int> a(10);
	std::vector<int> b(10);

	std::cout << "A_size=" << a.size() << " A_cap=" << a.capacity() << " B_size=" << b.size() << " B_cap=" << b.capacity() << std::endl;
	a.resize(5);
	b.resize(5);
	std::cout << "A_size=" << a.size() << " A_cap=" << a.capacity() << " B_size=" << b.size() << " B_cap=" << b.capacity() << std::endl;
	a.resize(12);
	b.resize(12);
	std::cout << "A_size=" << a.size() << " A_cap=" << a.capacity() << " B_size=" << b.size() << " B_cap=" << b.capacity() << std::endl;
	a.resize(10);
	b.resize(10);
	std::cout << "A_size=" << a.size() << " A_cap=" << a.capacity() << " B_size=" << b.size() << " B_cap=" << b.capacity() << std::endl;
	
}