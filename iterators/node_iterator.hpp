#pragma once

#include "../utils/utils.hpp"

namespace ft
{
	template <typename T>
	class node_iterator
	{
	public:
		typedef ft::bidirectional_iterator_tag						iterator_category;
		typedef typename ft::iterator_traits<T*>::value_type		value_type;
		typedef typename ft::iterator_traits<T*>::reference			reference;
		typedef typename ft::iterator_traits<T*>::pointer			pointer;
		typedef typename ft::iterator_traits<T*>::difference_type	difference_type;
		typedef ft::Node<value_type>*									node_pointer;
	protected:
		node_pointer _iter;

		node_pointer tree_min(node_pointer n) const
		{
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
		node_iterator() {};
		node_iterator(node_pointer x) : _iter(x) {}
		node_iterator(const node_iterator<value_type>& x) : _iter(x.iter()) {}
		node_iterator& operator= (const node_iterator<value_type>& x)
		{
			_iter = x.iter();
			return *this;
		}

		pointer operator->() const { return _iter->_val; }
		reference operator*() const { return *(_iter->_val); }
		node_pointer iter() { return _iter; }
		node_pointer iter() const { return _iter; }

		node_iterator& operator++()
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

		node_iterator& operator--()
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

		node_iterator operator++(int)
		{
			node_iterator temp = *this;

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

		node_iterator operator--(int)
		{
			node_iterator temp = *this;
			
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
	bool operator==(const node_iterator<A> & lhs, const node_iterator<B> & rhs){
		return (lhs.iter() == rhs.iter());
	}

	template<typename A, typename B>
	bool operator!=(const node_iterator<A> & lhs, const node_iterator<B> & rhs){
		return (lhs.iter() != rhs.iter());
	}
}