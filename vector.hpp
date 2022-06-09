# include <iostream>
#include <iterator>
# include <sstream>


namespace ft
{
template <class T, class Alloc = std::allocator<T> >

class vector
{
public:

//////////////////////////////
	// Enable If
	//////////////////////////////

	template <bool B, class Z = void>
	struct enable_if {};

	template <class Z>
	struct enable_if<true, Z> { typedef Z type; };

	//////////////////////////////
	// Is Same
	//////////////////////////////

	template <class Z, class U>
	struct is_same { static const bool value = false; };

	template <class Z>
	struct is_same<Z, Z> { static const bool value = true; };

	//////////////////////////////
	// Conditional
	//////////////////////////////

	template <bool B, class Z = void, class U = void>
	struct conditional {};

	template <class Z, class U>
	struct conditional<true, Z, U> { typedef Z type; };

	template <class Z, class U>
	struct conditional<false, Z, U> { typedef U type; };

template <bool IsConst>
	class vectorIterator {
	public:
		// Member types
		typedef typename		conditional<IsConst, const T, T>::type			value_type;
		typedef					std::ptrdiff_t										difference_type;
		typedef					std::size_t											size_type;
		// -structors
		vectorIterator			(void)												{ _ptr = NULL; }
		~vectorIterator			(void)												{}
		// Const stuff
		template <bool B>		vectorIterator
			(const vectorIterator<B> & x, typename enable_if<!B>::type* = 0)	{ _ptr = x.getPtr(); }

		// Assignment
		vectorIterator &		operator=	(const vectorIterator & x)				{ _ptr = x.getPtr(); return (*this); }
		vectorIterator &		operator+=	(int n)									{ _ptr += n; return (*this); }
		vectorIterator &		operator-=	(int n)									{ _ptr -= n; return (*this); }
		// Comparison
		template <bool B> bool	operator==	(const vectorIterator<B> & x) const		{ return (_ptr == x.getPtr()); }
		template <bool B> bool	operator!=	(const vectorIterator<B> & x) const		{ return (_ptr != x.getPtr()); }
		template <bool B> bool	operator<	(const vectorIterator<B> & x) const		{ return (_ptr < x.getPtr()); }
		template <bool B> bool	operator>	(const vectorIterator<B> & x) const		{ return (_ptr > x.getPtr()); }
		template <bool B> bool	operator<=	(const vectorIterator<B> & x) const		{ return (_ptr <= x.getPtr()); }
		template <bool B> bool	operator>=	(const vectorIterator<B> & x) const		{ return (_ptr >= x.getPtr()); }
		// -crementation
		vectorIterator &		operator++	(void)									{ _ptr++; return (*this); }
		vectorIterator &		operator--	(void)									{ _ptr--; return (*this); }
		vectorIterator			operator++	(int)									{ vectorIterator<IsConst> x(*this); _ptr++; return (x); }
		vectorIterator			operator--	(int)									{ vectorIterator<IsConst> x(*this); _ptr--; return (x); }
		// Operation
		vectorIterator			operator+	(int n) const							{ return (_ptr + n); }
		vectorIterator			operator-	(int n) const							{ return (_ptr - n); }
		difference_type			operator-	(const vectorIterator & x) const		{ return (_ptr - x.getPtr()); }
		// Dereference
		value_type &			operator[]	(size_type n) const						{ return (*(_ptr + n)); }
		value_type &			operator*	(void) const							{ return (*_ptr); }
		value_type *			operator->	(void) const							{ return (_ptr); }
		// Member functions
		value_type *			getPtr		(void) const							{ return (_ptr); }
		// Friend functions
		friend vectorIterator	operator+	(int n, const vectorIterator & x)		{ return (x.getPtr() + n); }

// # if __APPLE__
// 		friend class			vector;
// 		friend class			reverse_iterator<vectorIterator>;
// 	private:
// # endif
		vectorIterator			(value_type * const ptr)							{ _ptr = ptr; }

	private:
		value_type *			_ptr;
	};

	typedef T															value_type;
	typedef	Alloc														allocator_type;
	typedef typename allocator_type::reference							reference;
	typedef typename allocator_type::const_reference					const_reference;
	typedef typename allocator_type::pointer							pointer;
	typedef typename allocator_type::const_pointer						const_pointer;
	typedef		vectorIterator<false>							iterator;
	typedef		vectorIterator<true>							const_iterator;
	// typedef		reverse_iterator<iterator>					reverse_iterator;
	// typedef		reverse_iterator<const_iterator>			const_reverse_iterator;
	typedef typename vectorIterator<false>::difference_type				difference_type;
	typedef typename vectorIterator<false>::size_type		size_type;

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

	reference front() {
		return (*_arr);
	}

	const_reference front() const {
		return (*_arr);
	}

	reference back() {
		return (*(_arr + _size - 1));
	}

	const_reference back() const {
		return (*(_arr + _size - 1));
	}

	template <typename S>
	std::string to_string (S n)
	{
		std::ostringstream	ss;
		ss << n;
		return (ss.str());
	}

	reference operator[] (size_type n) const
	{
		return (*(_arr + n));
	}

	reference at (size_type n)
	{
		if (n >= _size)
		{
			throw std::out_of_range("vector::_M_range_check: __n (which is " + to_string(n) + ") >= this->size() (which is " + to_string(_size) + ")");
		}
		return (_arr[n]);
	}

	const_reference at (size_type n) const
	{
		if (n >= _size)
		{
			throw std::out_of_range("vector::_M_range_check: __n (which is " + to_string(n) + ") >= this->size() (which is " + to_string(_size) + ")");
		}
		return (_arr[n]);
	}

		//////////////////////////////
	// Iterators
	//////////////////////////////

	iterator begin (void)
	{
		return (iterator(_arr));
	}

	const_iterator begin (void) const
	{
		return (const_iterator(_arr));
	}

	iterator end (void)
	{
		return (iterator(_arr + _size));
	}

	const_iterator end (void) const
	{
		return (const_iterator(_arr + _size));
	}

	////////////////////////////
	// Reverse iterators
	////////////////////////////

	// reverse_iterator rbegin (void)
	// {
	// 	return (reverse_iterator(_arr + _size - 1));
	// }

	// const_reverse_iterator rbegin (void) const
	// {
	// 	return (const_reverse_iterator(_arr + _size - 1));
	// }

	// reverse_iterator rend (void)
	// {
	// 	return (reverse_iterator(_arr - 1));
	// }

	// const_reverse_iterator rend (void) const
	// {
	// 	return (const_reverse_iterator(_arr - 1));
	// }


private:
	pointer			_arr;
	size_type 		_size;
	size_type 		_capacity;
	allocator_type	_alloc;
};
}