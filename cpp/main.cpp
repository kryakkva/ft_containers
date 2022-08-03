#include <map>
#include <set>
#include <iostream>
#include <list>
#include "../set.hpp"

#define TESTED_NAMESPACE ft

template <typename T>
class foo {
	public:
		typedef T	value_type;

		foo(void) : value(), _verbose(false) { };
		foo(value_type src, const bool verbose = false) : value(src), _verbose(verbose) { };
		foo(foo const &src, const bool verbose = false) : value(src.value), _verbose(verbose) { };
		~foo(void) { if (this->_verbose) std::cout << "~foo::foo()" << std::endl; };
		void m(void) { std::cout << "foo::m called [" << this->value << "]" << std::endl; };
		void m(void) const { std::cout << "foo::m const called [" << this->value << "]" << std::endl; };
		foo &operator=(value_type src) { this->value = src; return *this; };
		foo &operator=(foo const &src) {
			if (this->_verbose || src._verbose)
				std::cout << "foo::operator=(foo) CALLED" << std::endl;
			this->value = src.value;
			return *this;
		};
		value_type	getValue(void) const { return this->value; };
		void		switchVerbose(void) { this->_verbose = !(this->_verbose); };

		operator value_type(void) const {
			return value_type(this->value);
		}
	private:
		value_type	value;
		bool		_verbose;
};

#define T1 foo<int>
// #define T2 std::string
#define _pair TESTED_NAMESPACE::pair

// typedef TESTED_NAMESPACE::map<T1, T2>::value_type T3;

typedef TESTED_NAMESPACE::set<T1>::iterator ft_iterator;
typedef TESTED_NAMESPACE::set<T1>::const_iterator ft_const_iterator;
// typedef _pair<const T1, T2> T3;

// typedef _pair<const T1, T2> T3;

// static unsigned int i = 0;
// static int iter = 0;

template <typename T>
std::string	printPair(const T &iterator, bool nl = true, std::ostream &o = std::cout)
{
	o << "value: " << *iterator;
	if (nl)
		o << std::endl;
	return ("");
}

template <typename T_MAP>
void	printSize(T_MAP const &mp, bool print_content = 1)
{
	std::cout << "size: " << mp.size() << std::endl;
	std::cout << "max_size: " << mp.max_size() << std::endl;
	if (print_content)
	{
		typename T_MAP::const_iterator it = mp.begin(), ite = mp.end();
		// --ite;
		// std::cout << "IT " << ite->first << std::endl;
		// ++ite;
		std::cout << std::endl << "Content is:" << std::endl;
		for (; it != ite; ++it)
		{
			// std::cout << "ITER " <<  << std::endl;
			std::cout << "- " << printPair(it, false) << std::endl;
		}
	}
	std::cout << "###############################################" << std::endl;
}

template <typename T>
T	inc(T it, int n)
{
	while (n-- > 0)
		++it;
	return (it);
}

template <typename T>
T	dec(T it, int n)
{
	while (n-- > 0)
		--it;
	return (it);
}

// template <typename TT1, typename TT2>
// void	printReverse(TESTED_NAMESPACE::map<TT1, TT2> &mp)
// {
// 	typename TESTED_NAMESPACE::map<TT1, TT2>::iterator it = mp.end(), ite = mp.begin();

// 	std::cout << "printReverse:" << std::endl;
// 	while (it != ite) {
// 		it--;
// 		std::cout << "-> " << printPair(it, false) << std::endl;
// 	}
// 	std::cout << "_______________________________________________" << std::endl;
// }

// template <typename SET>
// void	ft_bound(SET &st, const T1 &param)
// {
// 	ft_iterator ite = st.end(), it[2];
// 	_pair<ft_iterator, ft_iterator> ft_range;

// 	std::cout << "\t-- [" << iter++ << "] --" << std::endl;
// 	std::cout << "with key [" << param << "]:" << std::endl;
// 	it[0] = st.lower_bound(param); it[1] = st.upper_bound(param);
// 	ft_range = st.equal_range(param);
// 	std::cout << "lower_bound: " << (it[0] == ite ? "end()" : printPair(it[0], false)) << std::endl;
// 	std::cout << "upper_bound: " << (it[1] == ite ? "end()" : printPair(it[1], false)) << std::endl;
// 	std::cout << "equal_range: " << (ft_range.first == it[0] && ft_range.second == it[1]) << std::endl;
// }

// template <typename SET>
// void	ft_const_bound(const SET &st, const T1 &param)
// {
// 	ft_const_iterator ite = st.end(), it[2];
// 	_pair<ft_const_iterator, ft_const_iterator> ft_range;

// 	std::cout << "\t-- [" << iter++ << "] (const) --" << std::endl;
// 	std::cout << "with key [" << param << "]:" << std::endl;
// 	it[0] = st.lower_bound(param); it[1] = st.upper_bound(param);
// 	ft_range = st.equal_range(param);
// 	std::cout << "lower_bound: " << (it[0] == ite ? "end()" : printPair(it[0], false)) << std::endl;
// 	std::cout << "upper_bound: " << (it[1] == ite ? "end()" : printPair(it[1], false)) << std::endl;
// 	std::cout << "equal_range: " << (ft_range.first == it[0] && ft_range.second == it[1]) << std::endl;
// }

int		main(void)
{
	std::list<T1> lst;
	unsigned int lst_size = 5;
	for (unsigned int i = 0; i < lst_size; ++i)
		lst.push_back((i + 1) * 7);

	TESTED_NAMESPACE::set<T1> st(lst.begin(), lst.end());
	TESTED_NAMESPACE::set<T1>::reverse_iterator it(st.rbegin());
	TESTED_NAMESPACE::set<T1>::const_reverse_iterator ite(st.rbegin());
	printSize(st);

	printPair(++ite);
	printPair(ite++);
	printPair(ite++);
	printPair(++ite);

	it->m();
	ite->m();

	printPair(++it);
	printPair(it++);
	printPair(it++);
	printPair(++it);

	printPair(--ite);
	printPair(ite--);
	printPair(--ite);
	printPair(ite--);

	(*it).m();
	(*ite).m();

	printPair(--it);
	printPair(it--);
	printPair(it--);
	printPair(--it);

	return (0);
}
