#pragma once

// #include <iterator>
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
		typedef ft::random_access_iterator_tag	iterator_category;
	};

	template <class T>
	struct iterator_traits<const T*>
	{
		typedef ptrdiff_t						difference_type;
		typedef T								value_type;
		typedef const T*						pointer;
		typedef const T&						reference;
		typedef ft::random_access_iterator_tag	iterator_category;
	};

	template <class T, bool isConst>
	class vector_iterator
	{
	public:
		typedef T													value_type;
		typedef ptrdiff_t											difference_type;
		typedef typename ft::IsConst<isConst, T*, const T*>::type	pointer;
		typedef typename ft::IsConst<isConst, T&, const T&>::type	reference;
		typedef ft::random_access_iterator_tag						iterator_category;
	protected:
		pointer _iter;
	public:
		vector_iterator() {};
		vector_iterator(pointer x) : _iter(x) {}
		vector_iterator(const vector_iterator<T, false>& x) : _iter(&(*x)) {}
		vector_iterator& operator= (const vector_iterator& x)
		{
			// if (this != &x)
			// {
				_iter = &(*x);
			// }
			return *this;
		}

		virtual ~vector_iterator() {}

		pointer base() const { return _iter; }

		reference operator* () const { return *_iter; }
		pointer operator-> () const { return _iter; }

		vector_iterator& operator++ () { ++_iter; return *this; }
		vector_iterator& operator-- () { --_iter; return *this; }

		vector_iterator operator++(int)
		{
			vector_iterator tmp = *this;
			++(*this);
			return tmp;
		}

		vector_iterator operator--(int)
		{
			vector_iterator tmp(*this);
			--(*this);
			return tmp;
		}

		vector_iterator operator+(difference_type n) const
		{
			return (_iter + n);
		}

		vector_iterator& operator+=(difference_type n)
		{
			_iter += n;
			return (*this);
		}

		vector_iterator operator-(difference_type n) const
		{
			return (_iter - n);
		}

		vector_iterator& operator-=(difference_type n)
		{
			_iter -= n;
			return (*this);
		}


		reference operator[](difference_type n) const
		{
			return (*(_iter + n));
		}

		difference_type operator-(vector_iterator it) const
		{
			return (this->_iter - it._iter);
		}

		difference_type operator+(vector_iterator it) const
		{
			return (this->_iter + it._iter);
		}

		friend vector_iterator operator+(difference_type n, const vector_iterator& it)
		{
			vector_iterator newIt(it);
			return (newIt += n);
		}

		friend vector_iterator operator-(difference_type n, const vector_iterator& it)
		{
			vector_iterator newIt(it);
			return (newIt -= n);
		}
	};

	template <class It_l, class It_r>
	bool operator==(const It_l& it_l, const It_r& it_r)
	{
		return(&(*it_l) == &(*it_r));
	}

	template <class It_l, class It_r>
	bool operator!=(const It_l& it_l, const It_r& it_r)
	{
		// return(&(*it_l) != &(*it_r));
		return !(it_l == it_r);
	}

	template <class It_l, class It_r>
	bool operator<(const It_l& it_l, const It_r& it_r)
	{
		return(&(*it_l) < &(*it_r));
	}

	template <class It_l, class It_r>
	bool operator>(const It_l& it_l, const It_r& it_r)
	{
		return it_r < it_l;
		// return(&(*it_l) > &(*it_r));
	}

	template <class It_l, class It_r>
	bool operator<=(const It_l& it_l, const It_r& it_r)
	{
		return !(it_r < it_l);
		// return(&(*it_l) <= &(*it_r));
	}

	template <class It_l, class It_r>
	bool operator>=(const It_l& it_l, const It_r& it_r)
	{
		return !(it_l < it_r);
		// return(&(*it_l) >= &(*it_r));
	}
}