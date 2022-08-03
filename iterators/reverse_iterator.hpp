#pragma once

#include "../utils/utils.hpp"

namespace ft
{
template <class Iterator>
class reverse_iterator : public Iterator
{
protected:
	Iterator current;
public:
	typedef Iterator							iterator_type;
	typedef typename Iterator::difference_type	difference_type;
	typedef typename Iterator::reference		reference;
	typedef typename Iterator::pointer			pointer;
	typedef typename Iterator::const_reference		const_reference;
	typedef typename Iterator::const_pointer			const_pointer;

	explicit reverse_iterator(iterator_type x = 0) : current(x) { }

	template <class Iter>
	reverse_iterator(const reverse_iterator<Iter>& rev_it) : current(rev_it.base()) { }

	iterator_type base() const { return current; }

	template <class U>
	reverse_iterator& operator=(const reverse_iterator<U>& u)
	{
		current = u.base();
		return *this;
	}

	reference operator*() { iterator_type tmp = current; return *(--tmp); }
	pointer operator->() { return (&(operator*())); }
	
	const_reference operator*() const { iterator_type tmp = current; return *(--tmp); }
	const_pointer operator->() const { return (&(operator*())); }

	reverse_iterator &operator++() { --current; return (*this); }
	reverse_iterator operator++(int) { reverse_iterator tmp(*this); --current; return (tmp); }
	reverse_iterator &operator--() { ++current; return (*this); }
	reverse_iterator operator--(int) { reverse_iterator tmp(*this); ++current; return (tmp); }

	reverse_iterator operator+(difference_type n) const { return reverse_iterator(current - n); }
	reverse_iterator& operator+=(difference_type n) { current -= n; return *this; }
	reverse_iterator operator-(difference_type n) const { return reverse_iterator(current + n); }
	reverse_iterator& operator-=(difference_type n) { current += n; return *this; }

	difference_type operator-(reverse_iterator it) const { return (it.current - this->current); }
	difference_type operator+(reverse_iterator it) const { return (it.current + this->current); }

	reference	operator[](difference_type n) const { return *(*this + n); }

	friend reverse_iterator operator+(difference_type n, const reverse_iterator& it)
	{
		return (reverse_iterator(it + n));
	}

	friend reverse_iterator operator-(difference_type n, const reverse_iterator& it)
	{
		return (reverse_iterator(it - n));
	}

};

template <class Iter1, class Iter2>
bool operator==(const reverse_iterator<Iter1>& x, const reverse_iterator<Iter2>& y)
	{
		return (x.base() == y.base());
	}

template <class Iter1, class Iter2>
bool operator!=(const reverse_iterator<Iter1>& x, const reverse_iterator<Iter2>& y)
	{
		return (x.base() != y.base());
	}

template <class Iter1, class Iter2>
bool operator<(const reverse_iterator<Iter1>& x, const reverse_iterator<Iter2>& y)
	{
		return (x.base() > y.base());
	}

template <class Iter1, class Iter2>
bool operator>(const reverse_iterator<Iter1>& x, const reverse_iterator<Iter2>& y)
	{
		return (x.base() < y.base());
	}

template <class Iter1, class Iter2>
bool operator<=(const reverse_iterator<Iter1>& x, const reverse_iterator<Iter2>& y)
	{
		return (x.base() >= y.base());
	}

template <class Iter1, class Iter2>
bool operator>=(const reverse_iterator<Iter1>& x, const reverse_iterator<Iter2>& y)
	{
		return (x.base() <= y.base());
	}
}