#include <vector>
#include "vector.hpp"

#define NM ft

using namespace NM;

int main()

{
	vector<int> vec_1;
	vector<int> vec_2;

	for (size_t i = 0; i < 16; i++)
	{
		vec_1.push_back(i);
		vec_2.push_back(i * 2);
	}
	std::cout << vec_1.capacity() << "	" << vec_2.capacity() << std::endl;
	std::cout << vec_1.size() << "	" << vec_2.size() << std::endl;

	// while (it_1 != vec_1.end())
	// {
	// 	++it_1;
	// 	++it_2;
	// }
	std::cout << std::endl;
	std::cout << "BEGIN " << *vec_2.begin() << std::endl;
	// vec_2.insert(vec_2.begin() + 2, vec_1.begin(), vec_1.begin() + 4);
	vec_2.insert(vec_2.begin() + 2, 8, 123);
	// std::cout << vec_1.capacity() << "	" << vec_2.capacity() << std::endl;
	// std::cout << vec_1.size() << "	" << vec_2.size() << std::endl;
	// vec_1.swap(vec_2);
	vector<int>::iterator it_1 = vec_1.begin();
	vector<int>::iterator it_2 = vec_2.begin();
	it_1 = vec_1.begin();
	it_2 = vec_2.begin();
	while (it_2 != vec_2.end())
	{
		std::cout << *it_1 << "	" << *it_2 << std::endl;
		++it_1;
		++it_2;
	}
	return 0;
}

/*		
{
		std::string str("kheabsdj,ad");
		vector<std::string> vec_1(10, str);
		std::string *str;
		std::string s("Test");
		std::allocator<std::string> all;
		str = all.allocate(10);
		for (size_t i = 0; i < 10; i++)
		{
			all.construct(&str[i], (s + std::to_string(i) + " "));
		}
		for (size_t i = 0; i < 10; i++)
		{
			std::cout << str[i];
		}
		std::cout << std::endl;
		for (size_t i = 0; i < 10; i++)
		{
			all.destroy(&str[i]);
		}
		all.deallocate(str, 10);
		std::vector<std::string> v(10);
		v[0] = "qasfdfsd";
		for (size_t i = 0; i < 10; i++)
		{
			std::cout << " " << i << str[i];
		}
		std::cout << std::endl;
		return 0;
}
*/		