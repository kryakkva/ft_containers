#pragma once

#include "../utils/utils.hpp"

namespace ft
{
	// template <class T>
	// struct iterator_traits<T*>
	// {
	// 	typedef ptrdiff_t						difference_type;
	// 	typedef T								value_type;
	// 	typedef T*								pointer;
	// 	typedef T&								reference;
	// 	typedef ft::bidirectional_iterator_tag	iterator_category;
	// };

	// template <class T>
	// struct iterator_traits<const T*>
	// {
	// 	typedef ptrdiff_t						difference_type;
	// 	typedef const T							value_type;
	// 	typedef const T*						pointer;
	// 	typedef const T&						reference;
	// 	typedef ft::bidirectional_iterator_tag	iterator_category;
	// };

	template <typename T>
	class map_iterator
	{
	public:
		typedef ft::bidirectional_iterator_tag												iterator_category;
		typedef typename ft::iterator_traits<T*>::value_type								value_type;
		typedef typename ft::iterator_traits<T*>::reference									reference;
		typedef typename ft::iterator_traits<T*>::pointer									pointer;
		typedef typename ft::iterator_traits<T*>::difference_type							difference_type;
		typedef Node<typename ft::remove_const<value_type>::type>*							node_pointer;
		// typedef Node<value_type>*							node_pointer;
	protected:
		node_pointer _iter;

		node_pointer tree_min(node_pointer n) const
		{
			// std::cout << "TEST " << std::endl;
			while (n->_left != NULL && !n->_left->_isNil)
			{
				n = n->_left;
			}
			return n;
		}

		node_pointer tree_max(node_pointer n) const
		{
			while (!n->_right->_isNil)
				n = n->_right;
			return n;
		}
	public:
		map_iterator() {};
		map_iterator(node_pointer x) : _iter(x) {}
		map_iterator(const map_iterator<typename ft::remove_const<value_type>::type>& x) { *this = x; }
		map_iterator& operator= (const map_iterator<typename ft::remove_const<value_type>::type>& x)
		{
			_iter = x.iter();
			return *this;
		}

		pointer operator->() const {
			return _iter->_val;
		}

		reference operator*() const {
			return *(_iter->_val);
		}

		node_pointer iter() const {
			return _iter;
		}

		map_iterator& operator++()
		{
			if (_iter->_right && !_iter->_right->_isNil)
			{
				_iter = tree_min(_iter->_right);
			}
			else {
				node_pointer tmp = _iter->_parent;
				while (tmp != NULL && _iter == tmp->_right) {
					_iter = tmp;
					tmp = tmp->_parent;
				}
				_iter = tmp;
			}
			return *this;
		}

		map_iterator& operator--()
		{
			if (_iter->_left && !_iter->_left->_isNil)
			{
				_iter = tree_max(_iter->_left);
			}
			else {
				node_pointer tmp = _iter->_parent;
				while (tmp != NULL && _iter == tmp->_left) {
					_iter = tmp;
					tmp = tmp->_parent;
				}
				_iter = tmp;
			}
			return *this;
		}

		map_iterator operator++(int) {
			map_iterator temp = *this;
			if (!_iter->_right->_isNil) {
				_iter = tree_min(_iter->_right);
			}
			else {
				node_pointer y = _iter->_parent;
				while (y != NULL && _iter == y->_right) {
					_iter = y;
					y = y->_parent;
				}
				_iter = y;
			}
			return temp;
		}

		map_iterator operator--(int) {
			map_iterator temp = *this;
			if (_iter->_left &&!_iter->_left->_isNil) {
				_iter = tree_max(_iter->_left);
			}
			else {
				node_pointer y = _iter->_parent;
				while (y != NULL && _iter == y->_left) {
					_iter = y;
					y = y->_parent;
				}
				_iter = y;
			}
			return temp;
		}
	};

	template<typename A, typename B>
	bool operator==(const map_iterator<A> & lhs, const map_iterator<B> & rhs){
		return (lhs.iter() == rhs.iter());
	}

	template<typename A, typename B>
	bool operator!=(const map_iterator<A> & lhs, const map_iterator<B> & rhs){
		return (lhs.iter() != rhs.iter());
	}
}