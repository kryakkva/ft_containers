#pragma once

#include "utils.hpp"

namespace ft
{
	template <class T>
	struct iterator_traits<T*>
	{
		typedef ptrdiff_t						difference_type;
		typedef T								value_type;
		typedef T*								pointer;
		typedef T&								reference;
		typedef ft::bidirectional_iterator_tag	iterator_category;
	};

	template <class T>
	struct iterator_traits<const T*>
	{
		typedef ptrdiff_t						difference_type;
		typedef T								value_type;
		typedef const T*						pointer;
		typedef const T&						reference;
		typedef ft::bidirectional_iterator_tag	iterator_category;
	};

	template <class T, bool is_const>
	class map_iterator
	{
	private:
		typedef T													value_type;
		typedef ptrdiff_t											difference_type;
		typedef typename ft::IsConst<isConst, T*, const T*>::type	pointer;
		typedef typename ft::IsConst<isConst, T&, const T&>::type	reference;
		typedef ft::random_access_iterator_tag						iterator_category;
	protected:
		pointer _iter;
	public:
		map_iterator() {};
		map_iterator(pointer x) : _iter(x) {}
		map_iterator(const map_iterator<T, false>& x) : _iter(&(*x)) {}
		map_iterator& operator= (const map_iterator& x)
		{
			// if (this != &x)
			// {
				_iter = &(*x);
			// }
			return *this;
		}
	};
}