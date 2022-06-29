#include "vector.hpp"
#include <vector>
#include <list>
#include <iostream>

#define TESTED_NAMESPACE std
#define T_SIZE_TYPE typename TESTED_NAMESPACE::vector<T>::size_type
#define TESTED_TYPE int
// #define TESTED_TYPE foo<int>


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

void	prepost_incdec(TESTED_NAMESPACE::vector<TESTED_TYPE> &vct)
{
	TESTED_NAMESPACE::vector<TESTED_TYPE>::iterator it = vct.begin();
	TESTED_NAMESPACE::vector<TESTED_TYPE>::iterator it_tmp;

	std::cout << "Pre inc" << std::endl;
	it_tmp = ++it;
	std::cout << *it_tmp << " | " << *it << std::endl;

	std::cout << "Pre dec" << std::endl;
	it_tmp = --it;
	std::cout << *it_tmp << " | " << *it << std::endl;

	std::cout << "Post inc" << std::endl;
	it_tmp = it++;
	std::cout << *it_tmp << " | " << *it << std::endl;

	std::cout << "Post dec" << std::endl;
	it_tmp = it--;
	std::cout << *it_tmp << " | " << *it << std::endl;
	std::cout << "###############################################" << std::endl;
}

	void	is_empty(TESTED_NAMESPACE::vector<int> const &vct)
{
	std::cout << "is_empty: " << vct.empty() << std::endl;
}

template <typename T>
void	printSize(TESTED_NAMESPACE::vector<T> const &vct, bool print_content = true)
{
	const T_SIZE_TYPE size = vct.size();
	const T_SIZE_TYPE capacity = vct.capacity();
	const std::string isCapacityOk = (capacity >= size) ? "OK" : "KO";
	// Cannot limit capacity's max value because it's implementation dependent

	std::cout << "size: " << size << std::endl;
	std::cout << "capacity: " << isCapacityOk << std::endl;
	std::cout << "max_size: " << vct.max_size() << std::endl;
	if (print_content)
	{
		typename TESTED_NAMESPACE::vector<T>::const_iterator it = vct.begin();
		typename TESTED_NAMESPACE::vector<T>::const_iterator ite = vct.end();
		std::cout << std::endl << "Content is:" << std::endl;
		for (; it != ite; ++it)
			std::cout << "- " << *it << std::endl;
	}
	std::cout << "###############################################" << std::endl;
}


template <typename Ite_1, typename Ite_2>
void ft_eq_ope(const Ite_1 &first, const Ite_2 &second, const bool redo = 1)
{
	std::cout << (first < second) << std::endl;
	std::cout << (first <= second) << std::endl;
	std::cout << (first > second) << std::endl;
	std::cout << (first >= second) << std::endl;
	if (redo)
		ft_eq_ope(second, first, 0);
}

template <class T, class Alloc>
void	cmp(const TESTED_NAMESPACE::vector<T, Alloc> &lhs, const TESTED_NAMESPACE::vector<T, Alloc> &rhs)
{
	static int i = 0;

	std::cout << "############### [" << i++ << "] ###############"  << std::endl;
	std::cout << "eq: " << (lhs == rhs) << " | ne: " << (lhs != rhs) << std::endl;
	std::cout << "lt: " << (lhs <  rhs) << " | le: " << (lhs <= rhs) << std::endl;
	std::cout << "gt: " << (lhs >  rhs) << " | ge: " << (lhs >= rhs) << std::endl;
}

int		main(void)
{
	TESTED_NAMESPACE::vector<TESTED_TYPE> vct(4);
	TESTED_NAMESPACE::vector<TESTED_TYPE> vct2(4);

	cmp(vct, vct);  // 0
	cmp(vct, vct2); // 1

	vct2.resize(10);

	cmp(vct, vct2); // 2
	cmp(vct2, vct); // 3

	vct[2] = 42;

	cmp(vct, vct2); // 4
	cmp(vct2, vct); // 5

	swap(vct, vct2);

	cmp(vct, vct2); // 6
	cmp(vct2, vct); // 7

	return (0);
}