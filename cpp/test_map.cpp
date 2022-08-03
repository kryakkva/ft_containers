#include <set>
#include <iostream>
#include <list>
// #include "../nm/map.hpp"
#include "../set.hpp"

#define TESTED_NAMESPACE ft

int		main(void)
{
	TESTED_NAMESPACE::set<int> st;

	TESTED_NAMESPACE::set<int>::iterator ite = st.begin();
	*ite = 42; // < -- error as well ; T is always const, even with regular iterator
	return (0);
}