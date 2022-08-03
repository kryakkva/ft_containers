#pragma once

#include <iostream>
#include <iterator>

template <class value_type>
struct Node
{
	public:
	explicit Node(value_type* other = NULL) :
			_isRed(true), _isNil(false), _parent(NULL), _left(NULL), _right(NULL), _val(other) {}

	bool		_isRed;
	bool		_isNil;
	Node* 		_parent;
	Node*		_left;
	Node*		_right; 
	value_type*	_val;

	Node(const Node& other) { *this = other; }

	Node& operator=(const Node<value_type>& other)
	{
		_isRed = other._isRed;
		_isNil = other._isNil;
		_parent = other._parent;
		_left = other._left;
		_right = other._right;
		_val = other._val;
		return *this;
	}

	virtual ~Node() {}
};

namespace ft
{
	template <class S1, class S2>
	void ft_swap (S1 &a, S2 &b)
	{
		S1 tmp = a;
		a = b;
		b = tmp;
	}

// #######################################################################################
// ITERATOR
// #######################################################################################

	struct input_iterator_tag {};
	struct forward_iterator_tag		  : public input_iterator_tag {};
	struct bidirectional_iterator_tag : public forward_iterator_tag {};
	struct random_access_iterator_tag : public bidirectional_iterator_tag {};

	template <class Iterator>
	struct iterator_traits
	{
		typedef typename Iterator::difference_type		difference_type;
		typedef typename Iterator::value_type			value_type;
		typedef typename Iterator::pointer				pointer;
		typedef typename Iterator::reference			reference;
		typedef typename Iterator::iterator_category	iterator_category;
	};

	template <class T>
	struct iterator_traits<T*>
	{
		typedef ptrdiff_t						difference_type;
		typedef T								value_type;
		typedef T*								pointer;
		typedef T&								reference;
		typedef ft::random_access_iterator_tag	iterator_category;
	};

	template <class T>
	struct iterator_traits<const T*>
	{
		typedef ptrdiff_t						difference_type;
		typedef T							value_type;
		typedef const T*						pointer;
		typedef const T&						reference;
		typedef ft::random_access_iterator_tag	iterator_category;
	};

	template <class Category, class T, class Distance = ptrdiff_t,
			  class Pointer = T*, class Reference = T&>
	struct iterator
	{
		typedef T			value_type;
		typedef Distance	difference_type;
		typedef Pointer		pointer;
		typedef Reference	reference;
		typedef Category	iterator_category;
	};	

	template<class T>
	struct remove_const
	{
		typedef T type;
	};

	template<class T>
	struct remove_const <const T>
	{
		typedef T type;
	};
	
// #######################################################################################
// Enable if
// #######################################################################################

	template <bool B, class T = void>
    struct enable_if {};

    template <class T>
    struct enable_if<true, T> { typedef T type; };
            
// #######################################################################################
// Is integral
// #######################################################################################

	template <class T, bool v>
	struct integral_constant
	{
		static const bool value = v;
		typedef T						value_type;
		typedef integral_constant<T,v>	type;
		operator value_type() const { return v; }
	};

	template <class T>
	struct is_integral : public ft::integral_constant<T, false> {};

	template <>
	struct is_integral<bool> : public ft::integral_constant<bool, true>  {};
		
	template <>
	struct is_integral<char> : public ft::integral_constant<bool, true>  {};

	template <>
	struct is_integral<char16_t> : public ft::integral_constant<bool, true>  {};

	template <>
	struct is_integral<char32_t> : public ft::integral_constant<bool, true>  {};

	template <>
	struct is_integral<wchar_t> : public ft::integral_constant<bool, true>  {};

	template <>
	struct is_integral<signed char> : public ft::integral_constant<bool, true>  {};

	template <>
	struct is_integral<short int> : public ft::integral_constant<bool, true>  {};

	template <>
	struct is_integral<int> : public ft::integral_constant<bool, true>  {};

	template <>
	struct is_integral<long int> : public ft::integral_constant<bool, true>  {};

	template <>
	struct is_integral<long long int> : public ft::integral_constant<bool, true>  {};

	template <>
	struct is_integral<unsigned char> : public ft::integral_constant<bool, true>  {};

	template <>
	struct is_integral<unsigned short int> : public ft::integral_constant<bool, true>  {};

	template <>
	struct is_integral<unsigned int> : public ft::integral_constant<bool, true>  {};

	template <>
	struct is_integral<unsigned long int> : public ft::integral_constant<bool, true>  {};

	template <>
	struct is_integral<unsigned long long int> : public ft::integral_constant<bool, true>  {};

// #######################################################################################
// Pair
// #######################################################################################

	template <class T1, class T2> 
	struct pair
	{
		typedef T1 first_type;
		typedef T2 second_type;

		first_type first;
		second_type second;

		pair() : first(), second() { }

		template<class U, class V>
		pair (const pair<U,V>& pr) : first(pr.first), second(pr.second) { }

		pair (const first_type& a, const second_type& b) : first(a), second(b) { }

		pair& operator= (const pair& pr)
		{
			if (this != &pr)
			{
				first = pr.first;
				second = pr.second;
			}
			return *this;
		}
	};
///*
	template <class T1, class T2>
	bool operator==(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs) {
		return lhs.first == rhs.first && lhs.second == rhs.second;
	}

	template <class T1, class T2>
	bool operator!=(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs) {
		return !(lhs == rhs);
	}

	template <class T1, class T2>
	bool operator<(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs) {
		return lhs.first < rhs.first ||
			(!(rhs.first < lhs.first) && lhs.second < rhs.second);
	}

	template <class T1, class T2>
	bool operator<=(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs) {
		return !(rhs < lhs);
	}

	template <class T1, class T2>
	bool operator>(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs) {
		return rhs < lhs;
	}

	template <class T1, class T2>
	bool operator>=(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs) {
		return !(lhs < rhs);
	}
//*/
	template <class T1,class T2>
	pair<T1,T2> make_pair (T1 x, T2 y)
	{
		return ( pair<T1,T2>(x,y) );
	}
	
// #######################################################################################
// Lexicographical compare & equal
// #######################################################################################

	template <class InputIterator1, class InputIterator2>
	bool lexicographical_compare (InputIterator1 first1, InputIterator1 last1,
									InputIterator2 first2, InputIterator2 last2)
	{
		while (first1 != last1)
		{
			if (first2 == last2 || *first2 < *first1)
				return false;
			else if (*first1 < *first2)
			{
				return true;
			}
			++first1; ++first2;
		}
		return (first2 != last2);
	}

	template <class InputIterator1, class InputIterator2>
	bool equal ( InputIterator1 first1, InputIterator1 last1, InputIterator2 first2 )
	{
		while (first1!=last1) {
			if (!(*first1 == *first2))
				return false;
			++first1; ++first2;
		}
		return true;
	}
}