#pragma once

#include <iostream>
#include <iterator>
#include "utils.hpp"

#define ADD 1
#define SUBSTRACT 0

namespace ft
{
	template <class Iterator>
	class reverse_iterator;

	template <class Iterator>
	struct iterator_traits
	{
		typedef typename Iterator::value_type			value_type;
		typedef typename Iterator::difference_type		difference_type;
		typedef typename Iterator::pointer				pointer;
		typedef typename Iterator::reference			reference;
		typedef typename Iterator::iterator_category	iterator_category;
	};

	struct random_access_iterator_tag {};

	template <class T>
	struct iterator_traits <const T*>
	{
		typedef T								value_type;
		typedef ptrdiff_t						difference_type;
		typedef const T*						pointer;
		typedef const T&						reference;
		typedef ft::random_access_iterator_tag	iterator_category;
	};

	template <class T>
	struct iterator_traits<T*>
	{
		typedef T								value_type;
		typedef ptrdiff_t						difference_type;
		typedef T*								pointer;
		typedef T&								reference;
		typedef ft::random_access_iterator_tag	iterator_category;
	};

	template <class Category, class T, class Distance = ptrdiff_t, class Pointer = T*, class Reference = T&>
	struct iterator
	{
		typedef T			value_type;
		typedef Distance	difference_type;
		typedef Pointer		pointer;
		typedef Reference	reference;
		typedef Category	iterator_category;
	};

	template <typename T, bool isConst> 
	class vector_iterator
	{
	public:
		typedef T													value_type;
		typedef ptrdiff_t											difference_type;
		typedef typename ft::IsConst<isConst, T*, const T*>::type	pointer;
		typedef typename ft::IsConst<isConst, T&, const T&>::type	reference;
		typedef ft::random_access_iterator_tag						iterator_category;
		// typedef T*													valPtr;
	protected:
		pointer	_iter;
	public:
// #######################################################################################
// Constructors
// #######################################################################################
		vector_iterator(T* iter = 0) : _iter(iter) {}

		vector_iterator(const vector_iterator<T, false> &other) { _iter = other.getIter(); }

// #######################################################################################
// Assignment operator
// #######################################################################################

		vector_iterator& operator= (const vector_iterator<T, false> &other)
		{
			if (_iter != other.getIter()) {
				_iter = other.getIter();
			}
			return *this;
		}

// #######################################################################################
// Getter
// #######################################################################################

		pointer getIter() const { return _iter; }

// #######################################################################################
// Overload operators
// #######################################################################################

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

		bool operator==(const vector_iterator& it) const	{ return (it._iter == _iter); }
		bool operator!=(const vector_iterator& it) const	{ return (it._iter != _iter); }
		bool operator<(const vector_iterator& it) const		{ return (it._iter > _iter); }
		bool operator>(const vector_iterator& it) const		{ return (it._iter < _iter); }
		bool operator<=(const vector_iterator& it) const	{ return (it._iter >= _iter); }
		bool operator>=(const vector_iterator& it) const	{ return (it._iter <= _iter); }

		vector_iterator& operator+=(int nb)
			{
                movePtr(this->_iter, nb, ADD);
                return (*this);
            }

		vector_iterator operator+(int nb) const
            {
                vector_iterator it(*this);
                
                movePtr(it._iter, nb, ADD);
                return (it);
            }

		vector_iterator& operator-=(int nb)
            {
                movePtr(this->_iter, nb, SUBSTRACT);
                return (*this);
            }

		vector_iterator operator-(int nb) const
            {
                vector_iterator it(*this);
                
                movePtr(it._iter, nb, SUBSTRACT);
                return (it);
            }

		reference operator[](int nb) const
            {
                value_type* tmp(this->_iter);

                movePtr(tmp, nb, ADD);
                return (*tmp);
            }

		difference_type operator-(vector_iterator it) const
            {
                return (this->_iter - it._iter);
            }

		friend vector_iterator operator+(int nb, const vector_iterator& it)
            {
                vector_iterator newIt(it);
                return (newIt += nb);
            }

        friend vector_iterator operator-(int nb, const vector_iterator& it)
            {
                vector_iterator newIt(it);
                return (newIt -= nb);
            }

		private:
			void movePtr(pointer& val, long nb, bool sign) const
            {
                int mov;

                // If addtion, mov will be positive. If substraction, negative.
                if (sign == ADD)
                    mov = nb > 0 ? mov = 1: mov = -1;
                else
                    mov = nb > 0 ? mov = -1: mov = 1;

                if (nb < 0)
                    nb *= -1;
                for (; nb > 0; --nb)
                    val += mov;
            }
	};

	template <typename T, bool isConst>
	bool operator== (const vector_iterator<T, isConst>& lhs, const vector_iterator<T, isConst>& rhs)
	{
		return (lhs.getIter() == rhs.getIter());
	}

	template <typename T, bool isConst>
	bool operator!= (const vector_iterator<T, isConst>& lhs, const vector_iterator<T, isConst>& rhs)
	{
		return (lhs.getIter() != rhs.getIter());
	}
}