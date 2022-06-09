#pragma once

#include <iostream>
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

// ———————————————————————————————————————————————————————————————————————————————————————
// Constructors
// ———————————————————————————————————————————————————————————————————————————————————————

	explicit vector (const allocator_type& alloc = allocator_type())
	{
		_alloc = alloc;
		_size = 0;
		_capacity = 0;
		_arr = _alloc.allocate(0);
	}

	explicit vector (size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type())
	{
		_alloc = alloc;
		_size = n;
		_capacity = n;
		_arr = _alloc.allocate(n);

		for (size_type i = 0; i < _size; i++) {
			_alloc.construct(_arr + i, val);
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

// ———————————————————————————————————————————————————————————————————————————————————————
// Assignment operator
// ———————————————————————————————————————————————————————————————————————————————————————

	vector& operator= (const vector& x)
	{
		if(this != &x)
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

// ———————————————————————————————————————————————————————————————————————————————————————
// Destructor
// ———————————————————————————————————————————————————————————————————————————————————————

	~vector()
	{
		for (size_type i = 0; i < _size; i++)
		{
			_alloc.destroy(_arr + i);
		}
		_alloc.deallocate(_arr, _capacity);
	}

// ———————————————————————————————————————————————————————————————————————————————————————
// Capacity
// ———————————————————————————————————————————————————————————————————————————————————————

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
				for (; i < cap_tmp; i++) {
					_alloc.construct(tmp + i, val);
				}
				_alloc.deallocate(_arr, _capacity);
				_arr = tmp;
				_capacity = n;
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

	}

private:
	value_type 		*_arr;
	allocator_type	_alloc;
	size_type		_size;
	size_type		_capacity;
};
}
