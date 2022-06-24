#pragma once

#include <iterator>
#include "utils.hpp"

#define ADD 1
#define SUBSTRACT 0

namespace ft
{
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
		typedef T								value_type;
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
		// vector_iterator(const vector_iterator<typename remove_const<value_type>::type, false> & src) : _iter(&(*src)) {}
		// vector_iterator(const vector_iterator<T, true>& x) { _iter = const_cast<pointer>(x.base()); }
		vector_iterator& operator= (const vector_iterator& x)
		{
			// if (this != &x)
			// {
				_iter = &(*x);
			// }
			return *this;
		}

		~vector_iterator() {}

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

		// friend difference_type operator-(const vector_iterator& x, const vector_iterator& y)
		// {
		// 	return (x - y);
		// }

		// friend difference_type operator+(const vector_iterator& x, const vector_iterator& y)
		// {
		// 	return (x + y);
		// }

		// bool operator==(const vector_iterator& it) const	{ return (_iter == it._iter); }
		// bool operator!=(const vector_iterator& it) const	{ return (_iter != it._iter); }
		// bool operator<(const vector_iterator& it) const		{ return (_iter > it._iter); }
		// bool operator>(const vector_iterator& it) const		{ return (_iter < it._iter); }
		bool operator<=(const vector_iterator& it) const	{ return (_iter >= it._iter); }
		bool operator>=(const vector_iterator& it) const	{ return (_iter <= it._iter); }

		// friend bool operator==(const vector_iterator& it_l, const vector_iterator& it_R);
	private:
		void movePtr(pointer& val, long n, bool sign) const
		{
			int mov;

			// If addtion, mov will be positive. If substraction, negative.
			if (sign == ADD)
				mov = n > 0 ? mov = 1: mov = -1;
			else
				mov = n > 0 ? mov = -1: mov = 1;

			if (n < 0)
				n *= -1;
			for (; n > 0; --n)
				val += mov;
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
		return(&(*it_l) != &(*it_r));
	}

	template <class It_l, class It_r>
	bool operator<(const It_l& it_l, const It_r& it_r)
	{
		return(&(*it_l) < &(*it_r));
	}

	template <class It_l, class It_r>
	bool operator>(const It_l& it_l, const It_r& it_r)
	{
		return(&(*it_l) > &(*it_r));
	}

	template <class It_l, class It_r>
	bool operator<=(const It_l& it_l, const It_r& it_r)
	{
		return(&(*it_l) <= &(*it_r));
	}

	template <class It_l, class It_r>
	bool operator>=(const It_l& it_l, const It_r& it_r)
	{
		return(&(*it_l) >= &(*it_r));
	}
}