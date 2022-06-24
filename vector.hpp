#pragma once

#include <iostream>
#include <vector>
#include <iterator>
#include "iterator.hpp"
#include "reverse_iterator.hpp"

namespace ft
{
template < class T, class Alloc = std::allocator<T> >
class vector
{

public:
	typedef T											value_type;
	typedef Alloc										allocator_type;
	typedef typename allocator_type::reference			reference;
	typedef typename allocator_type::const_reference	const_reference;
	typedef typename allocator_type::pointer			pointer;
	typedef typename allocator_type::const_pointer		const_pointer;
	typedef ptrdiff_t									difference_type;
	typedef size_t										size_type;
	typedef	ft::vector_iterator<value_type, false>		iterator;
	typedef	ft::vector_iterator<value_type, true>		const_iterator;
	typedef ft::reverse_iterator<iterator>				reverse_iterator;
	typedef ft::reverse_iterator<const_iterator>		const_reverse_iterator;

private:
	void copy_construct(size_type idx, const_reference val)
	{
		new(&this->_arr[idx]) value_type(val);
	}
public:
// #######################################################################################
// Constructors
// #######################################################################################

	explicit vector (const allocator_type& alloc = allocator_type()) : _alloc(alloc), _size(0), _capacity(0)
	{
		_arr = _alloc.allocate(0);
	}

	explicit vector (size_type n,
					const value_type& val = value_type(),
					const allocator_type& alloc = allocator_type()) : _alloc(alloc), _size(n), _capacity(n)
	{
		_arr = _alloc.allocate(_capacity);

		for (size_type i = 0; i < _size; i++) {
			_alloc.construct(&_arr[i], val);
		}
	}

	template <class InputIterator>
	vector (InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type(),
			typename ft::enable_if<!ft::is_integral<InputIterator>::value>::type = 0) : _alloc(alloc), _size(0)
	{
		InputIterator tmp(first);

		while (tmp++ != last)
		{
			_size++;
		}
		
		_capacity = _size;
		_arr = _alloc.allocate(_capacity);

		for (size_type i = 0; first != last; ++i, ++first)
		{
			_alloc.construct(&_arr[i], *first);
		}
	}

	vector (const vector& x)
	{
		_alloc = x._alloc;
		_size = x._size;
		_capacity = x._capacity;
		_arr = _alloc.allocate(_capacity);

		for (size_type i = 0; i < _size; i++) {
			_alloc.construct(_arr + i, x[i]);
		}
		
	}

// #######################################################################################
// Assignment operator
// #######################################################################################

	vector& operator= (const vector& x)
	{
		if (this != &x)
		{
			for (size_type i = 0; i < _size; i++) {
				_alloc.destroy(_arr + i);
			}
			if (x._size > _capacity) {
				_alloc.deallocate(_arr, _capacity);
				_capacity = x._capacity;
				_arr = _alloc.allocate(_capacity);
			}
			_size = x._size;
			for (size_type i = 0; i < _size; i++) {
				_alloc.construct(_arr + i, x[i]);
			}
		}
		return (*this);
	}

// #######################################################################################
// Destructor
// #######################################################################################

	~vector()
	{
		for (size_type i = 0; i < _size; i++)
		{
			_alloc.destroy(_arr + i);
		}
		_alloc.deallocate(_arr, _capacity);
	}

// #######################################################################################
// Capacity
// #######################################################################################

	size_type size() const { return(_size); }
	size_type capacity() const { return(_capacity); }
	size_type max_size() const { return(allocator_type().max_size()); }
	bool empty() const { return(_size == 0); }

	void resize (size_type n, value_type val = value_type())
	{
		if (n < _size)
		{
			for (size_type i = n; i < _size; i++) {
				_alloc.destroy(_arr + i);	
			}
		}
		else
		{
			if (n > _capacity)
			{
				size_type cap_tmp;
				if (n > _capacity * 2)
					cap_tmp = n;
				else
					cap_tmp = _capacity * 2;
				reserve(n);
				for (size_type i = _size; i < cap_tmp; i++)
				{
					_alloc.construct(_arr + i, val);
				}
			}
			else
			{
				for (size_type i = _size; i < n; i++)
				{
					_alloc.construct(_arr + i, val);
				}
			}
		}
		_size = n;
	}

	void reserve (size_type n)
	{
		if (n > _capacity)
		{
			value_type	*tmp;
			size_type	cap_tmp;

			if (n > _capacity * 2)
			{
				cap_tmp = n;
				tmp = _alloc.allocate(cap_tmp);
			}
			else
			{
				cap_tmp = _capacity * 2;	
				tmp = _alloc.allocate(cap_tmp);
			}
			size_type i = 0;
			for (; i < _size; i++) {
				_alloc.construct(tmp + i, _arr[i]);
				_alloc.destroy(_arr + i);
			}
			_alloc.deallocate(_arr, _capacity);
			_arr = tmp;
			_capacity = cap_tmp;
		}
	}

// #######################################################################################
// Element access
// #######################################################################################

	reference operator[] (size_type n) { return(_arr[n]); }
	const_reference operator[] (size_type n) const { return(_arr[n]); }
	reference at (size_type n)
	{
		if (n > _size)
			throw std::out_of_range("vector");
		return(_arr[n]);
	}
	const_reference at (size_type n) const
	{
		if (n > _size)
			throw std::out_of_range("vector");
		return(_arr[n]);
	}
	reference front() { return(*_arr); }
	const_reference front() const { return(*_arr); }
	reference back() { return(*(_arr + _size - 1)); }
	const_reference back() const { return(*(_arr + _size - 1)); }

// #######################################################################################
// Modifiers
// #######################################################################################

	// ——————————————————————————————————————————————————————————————————————
	// Assign
	// ——————————————————————————————————————————————————————————————————————

	template <class InputIterator>
	void assign (InputIterator first, InputIterator last, typename ft::enable_if<!ft::is_integral<InputIterator>::value>::type = 0)
	{
		for (size_t i = 0; i < _size; i++)
		{
			_alloc.destroy(_arr + i);
		}
		size_type n = 0;
		InputIterator tmp(first);
		while (tmp++ != last)
		{
			n++;
		}
		
		if (n > _capacity)
		{
			_alloc.deallocate(_arr, _capacity);
			_arr = _alloc.allocate(n);	
			_capacity = n;
		}
		size_t i = 0;
		for (; first != last; ++i, ++first)
		{
			_alloc.construct(&_arr[i], *first);
		}
		_size = i;
	}

	void assign (size_type n, const value_type& val)
	{
		for (size_t i = 0; i < _size; i++)
		{
			_alloc.destroy(_arr + i);
		}
		if (n > _capacity)
		{
			_alloc.deallocate(_arr, _capacity);
			_arr = _alloc.allocate(n);	
			_capacity = n;
		}
		for (size_t i = 0; i < n; i++)
		{
			_alloc.construct(_arr + i, val);
		}
		_size = n;
	}

	// ——————————————————————————————————————————————————————————————————————
	// Push, Pop
	// ——————————————————————————————————————————————————————————————————————

	void push_back (const value_type& val)
	{
		if (_size == _capacity)
		{
			value_type	*tmp;
			size_type	cap_tmp;

			if(_capacity > 0)
				cap_tmp = _capacity * 2;
			else
				cap_tmp = 1;
			tmp = _alloc.allocate(cap_tmp);
			for (size_type i = 0; i < _size; i++)
			{
				_alloc.construct(tmp + i, _arr[i]);
				_alloc.destroy(_arr + i);
			}
			_alloc.deallocate(_arr, _capacity);
			_arr = tmp;
			_capacity = cap_tmp;
		}
		_alloc.construct(_arr + _size++, val);
	}

	void pop_back()
	{
		_alloc.destroy(_arr + _size--);
	}

	// ——————————————————————————————————————————————————————————————————————
	// Insert
	// ——————————————————————————————————————————————————————————————————————

	iterator insert(iterator position, const_reference val) {
		this->insert(position, 1, val);
		return (++position);
	}

	void insert(iterator position, size_type size, const_reference val) {
		iterator it = this->begin();
		if (this->_size + size >= this->_capacity)
			this->reserve(this->_size + size);
		size_type i = 0;
		while (it != position) {
			++it;
			++i;
		}
		// std::memmove
		for (size_type j = this->_size; j >= 1 && j >= i; j--)
			this->copy_construct(i + j + size - 1, this->_arr[j - 1]);
		for (size_type j = 0; j < size; j++)
			this->copy_construct(i + j, val);
		this->_size += size;
	}

	void insert(iterator position, iterator first, iterator last) {
		size_type size = last - first;
		iterator it = this->begin();
		if (this->_size + size >= this->_capacity)
			this->reserve(this->_size + size);
		size_type i = 0;
		while (it != position) {
			++it;
			++i;
		}
		// std::memmove
		for (size_type j = this->_size - 1; j > i + 1; j++)
			this->copy_construct(i + j + size, this->_arr[ + j - 1]);
		for (size_type j = 0; j < size; j++)
			this->copy_construct(i + j, *first++);
		this->_size += size;
	}
/*
	iterator insert (iterator position, const value_type& val)
	{

	}

    void insert (iterator position, size_type n, const value_type& val)
	{

	}

	template <class InputIterator>
    void insert (iterator position, InputIterator first, InputIterator last)
	{

	}

	// ——————————————————————————————————————————————————————————————————————
	// Erase
	// ——————————————————————————————————————————————————————————————————————

	iterator erase (iterator position)
	{

	}

	iterator erase (iterator first, iterator last)
	{

	}
*/
	// ——————————————————————————————————————————————————————————————————————
	// Swap, Clear
	// ——————————————————————————————————————————————————————————————————————

	void swap (vector& x)
	{
		swap(_alloc, x._alloc);
		swap(_size, x._size);
		swap(_capacity, x._capacity);
		swap(_arr, x._arr);
	}

	void clear()
	{
		for (size_type i = 0; i < _size; i++)
		{
			_alloc.destroy(&_arr[i]);
		}
		_size = 0;
	}

	iterator begin() { return iterator(_arr); }
	const_iterator begin() const { return const_iterator(_arr); }
	iterator end() { return iterator(_arr + _size); }
	const_iterator end() const { return const_iterator(_arr + _size); }
	reverse_iterator rbegin() { return reverse_iterator(end()); }
	const_reverse_iterator rbegin() const { return const_reverse_iterator(end()); }
	reverse_iterator rend() { return reverse_iterator(begin()); }
	const_reverse_iterator rend() const { return const_reverse_iterator(begin()); }

// #######################################################################################
// Non-member function overloads
// #######################################################################################

	// ——————————————————————————————————————————————————————————————————————
	// relational operators
	// ——————————————————————————————————————————————————————————————————————

	friend bool operator==(const vector& lhs, const vector& rhs)
	{
		if (lhs.size() != rhs.size())
			return false;

		for (ft::pair<const_iterator, const_iterator> it(lhs.begin(), rhs.begin());
				it.first != lhs.end(); ++it.first, ++it.second)
			if (*(it.first) != *(it.second))
				return false;
		return true;
	}

	friend bool operator!=(const vector& lhs, const vector& rhs)    { return !(lhs == rhs); }

	friend bool operator<(const vector& lhs, const vector& rhs)
	{
		for (ft::pair<const_iterator, const_iterator> it(lhs.begin(), rhs.begin());
				it.first != lhs.end() && it.second != rhs.end(); ++it.first, ++it.second)
			if (*(it.first) < *(it.second))
				return true;
		return (lhs.size() < rhs.size());
	}

	friend bool operator>(const vector& lhs, const vector& rhs)     { return rhs < lhs; }

	friend bool operator<=(const vector& lhs, const vector& rhs)    { return !(rhs < lhs); }
	
	friend bool operator>=(const vector& lhs, const vector& rhs)    { return !(lhs < rhs); }

	friend void swap (vector& x, vector& y)                         { 
		vector tmp(x);
		x = y;
		y = tmp;
	}

private:
	value_type 		*_arr;
	allocator_type	_alloc;
	size_type		_size;
	size_type		_capacity;
private:
	template <class S>
	void swap (S &a, S &b)
	{
		S tmp(a);
		a = b;
		b = tmp;
	}
};
}

