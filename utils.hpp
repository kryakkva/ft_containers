#pragma once
#include "iterator.hpp"

namespace ft
{
// #######################################################################################
// Is const
// #######################################################################################

	template <bool isConst, typename noConstType, typename ConstType>
	struct IsConst {};

	template <typename noConstType, typename ConstType>
	struct IsConst<true, noConstType, ConstType>
	{
		typedef ConstType type;
	};
	 
	template <typename noConstType, typename ConstType>
	struct IsConst<false, noConstType, ConstType>
	{
		typedef noConstType type;
	};

// #######################################################################################
// Enable if
// #######################################################################################

	template <bool B>
    struct enable_if {};

    template <>
    struct enable_if<true> { typedef int type; };
            
// #######################################################################################
// Is integral
// #######################################################################################

    template <typename T>
    struct is_integral { static const bool value = false; };

    template <>
    struct is_integral<bool> { static const bool value = true; };
        
    template <>
    struct is_integral<char> { static const bool value = true; };

    template <>
    struct is_integral<short> { static const bool value = true; };

    template <>
    struct is_integral<int> { static const bool value = true; };

    template <>
    struct is_integral<long> { static const bool value = true; };

    template <>
    struct is_integral<long long> { static const bool value = true; };

    template <>
    struct is_integral<unsigned char> { static const bool value = true; };

    template <>
    struct is_integral<unsigned short> { static const bool value = true; };

    template <>
    struct is_integral<unsigned int> { static const bool value = true; };

    template <>
    struct is_integral<unsigned long> { static const bool value = true; };

    template <>
    struct is_integral<unsigned long long> { static const bool value = true; };

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