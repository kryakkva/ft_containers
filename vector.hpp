#pragma once

#include "iterators/vector_iterator.hpp"
#include "iterators/reverse_iterator.hpp"

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
		if (n < 0)
			throw std::out_of_range("vector");
		_arr = _alloc.allocate(_capacity);
		size_type i = 0;
		for (; i < _size; i++) {
			try
			{
				_alloc.construct(&_arr[i], val);
			}
			catch(...)
			{
				freeAll(i);
				throw ;
			}			
		}
	}
	
	template <class InputIterator>
	vector (InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type(),
			typename ft::enable_if<!ft::is_integral<InputIterator>::value>::type = 0) : _alloc(alloc), _size(0), _capacity(0)
	{
		InputIterator tmp = first;
		while (tmp != last)
		{
			++tmp;
			++_size;
		}
		_capacity = _size;
		_arr = _alloc.allocate(_capacity);

		size_type i = 0;
		for (; first != last; i++, ++first)
		{
			try
			{
				_alloc.construct(&_arr[i], *first);
			}
			catch(...)
			{
				freeAll(i);
				throw ;
			}
			
		}
	}

	vector (const vector& x) : _alloc(x._alloc), _size(x._size), _capacity(x._size)
	{
		_arr = _alloc.allocate(_capacity);

		for (size_type i = 0; i < _size; i++)
		{
			try
			{
				_alloc.construct(_arr + i, x[i]);
			}
			catch(...)
			{
				freeAll(i);
				throw ;
			}
		}
		
	}

// #######################################################################################
// Assignment operator
// #######################################################################################

	vector& operator= (const vector& x)
	{
		if (this != &x)
		{
			for (size_type i = 0; i < _size; i++)
			{
				_alloc.destroy(_arr + i);
			}
			if (x._size > _capacity) {
				_alloc.deallocate(_arr, _capacity);
				_capacity = x._size;
				_arr = _alloc.allocate(_capacity);
			}
				// _capacity = x._size;
			_size = x._size;
			for (size_type i = 0; i < _size; i++)
			{
				try
				{
					_alloc.construct(_arr + i, x[i]);
				}
				catch(...)
				{
					freeAll(i);
					throw ;
				}
			}
			// std::cout << "TEST CAP=" << _capacity << std::endl;
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
					try
					{
						_alloc.construct(_arr + i, val);
					}
					catch(...)
					{
						freeAll(i);
						throw ;
					}
				}
			}
			else
			{
				for (size_type i = _size; i < n; i++)
				{
					try
					{
						_alloc.construct(_arr + i, val);
					}
					catch(...)
					{
						freeAll(i);
						throw ;
					}
				}
			}
		}
		_size = n;
	}

	void reserve (size_type n)
	{
		if (n > _capacity)
		{
			pointer	tmp;
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
			for (size_type i = 0; i < _size; i++)
			{
				try
				{
					_alloc.construct(&tmp[i], _arr[i]);
				}
				catch(...)
				{
					freeAll(i);
					throw ;
				}
				_alloc.destroy(&_arr[i]);
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
	void assign (InputIterator first, InputIterator last,
					typename ft::enable_if<!ft::is_integral<InputIterator>::value>::type = 0)
	{
		for (size_t i = 0; i < _size; i++)
		{
			_alloc.destroy(_arr + i);
		}
		// size_type n = last - first;
		size_type n = 0;
		InputIterator tmp = first;
		while (tmp != last)
		{
			++tmp;
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

	iterator insert(iterator pos, const_reference value) {
		int index = pos - begin();
		this->insert(pos, 1, value);
		return iterator(_arr + index);
	};

	void insert (iterator position, size_type n, const value_type& val)
	{
		size_type i = position - begin();
		size_type newSize = _size + n;
		if (newSize > _capacity)
		{
			reserve(newSize);
		}
		if (position != end())
		{
			for (size_type x = 1; x <= _size - i; x++)
			{
				_arr[newSize - x] = _arr[_size - x];
			}
		}
		for (; n > 0; i++, n--)
		{
			_alloc.construct(&_arr[i], val);
			// _arr[i] = val;
		}
		_size = newSize;	
	}

	template <class InputIterator>
	void insert(iterator position, InputIterator first, InputIterator last,
				typename ft::enable_if<!ft::is_integral<InputIterator>::value>::type = 0)
	{
		// size_type n = last - first;
		size_type n = 0;
		InputIterator tmp = first;
		while (tmp != last)
		{
			++tmp;
			n++;
		}
		if (!validate_iterators(first, last, n))
			throw std::exception();
		size_type i = position - begin();
		size_type newSize = _size + n;
		if (newSize > _capacity)
		{
			reserve(newSize);
		}
		for (size_type x = 1; x <= _size - i; x++)
		{
			_arr[newSize - x] = _arr[_size - x];
		}
		for (; n > 0; i++, n--)
		{
			_arr[i] = *first++;
		}
		_size = newSize;
	}

	// ——————————————————————————————————————————————————————————————————————
	// Erase
	// ——————————————————————————————————————————————————————————————————————

	iterator erase (iterator position)
	{
		if (position != end())
		{
			_size--;
			for (size_type i = position - begin(); i <= _size; i++)
			{
				_arr[i] = _arr[i + 1];
			}
		}
		return position;
	}

	iterator erase (iterator first, iterator last)
	{
		size_type i = first - begin();
		if (first < last)
		{
			size_type n = last - first;
			_size -= n;
			for (size_type x = i; x <= _size; x++)
			{
				_arr[x] = _arr[x + n];
			}
		}
		return _arr + i;
	}

	// ——————————————————————————————————————————————————————————————————————
	// Swap, Clear
	// ——————————————————————————————————————————————————————————————————————

	allocator_type get_allocator() const
	{
		return _alloc;
	}

	void swap (vector& x)
	{
		ft_swap(_size, x._size);
		ft_swap(_capacity, x._capacity);
		ft_swap(_arr, x._arr);
		ft_swap(_alloc, x._alloc);
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

private:
	pointer 		_arr;
	allocator_type	_alloc;
	size_type		_size;
	size_type		_capacity;
private:
	template <class S1, class S2>
	void ft_swap (S1 &a, S2 &b)
	{
		S1 tmp = a;
		a = b;
		b = tmp;
	}

	void freeAll(size_type i)
	{
		while (i)
		{
			_alloc.destroy(&_arr[--i]);
		}
		_alloc.deallocate(_arr, _capacity);
	}

	template<class InputIt>
	bool validate_iterators(InputIt first, InputIt last, size_t range) {
		pointer reserved_buffer;
		reserved_buffer = _alloc.allocate(range);
		bool result = true;
		size_t i = 0;

		for (;first != last; ++first, ++i) {
			try { reserved_buffer[i] = *first; }
			catch (...) { result = false; break; }
		}
		_alloc.deallocate(reserved_buffer, range);
		return result;
	}
};

// #######################################################################################
// Non-member function overloads
// #######################################################################################

template <class T, class Alloc>
void swap (vector<T, Alloc>& x, vector<T, Alloc>& y)
{ 
	x.swap(y);
}

template< class T, class Alloc >
bool operator==(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs)
{
	if (lhs.size() != rhs.size())
		return false;
	return ft::equal(lhs.begin(), lhs.end(), rhs.begin());
}

template< class T, class Alloc >
bool operator!=(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs)    { return !(lhs == rhs); }

template< class T, class Alloc >
bool operator< (const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs) {
	return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
}

template< class T, class Alloc >
bool operator>(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs)     { return rhs < lhs; }

template< class T, class Alloc >
bool operator<=(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs)    { return !(rhs < lhs); }

template< class T, class Alloc >
bool operator>=(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs)    { return !(lhs < rhs); }
}
