#pragma once

#include "utils/utils.hpp"
#include "utils/Tree.hpp"

namespace ft
{
	template <class T, class Compare = std::less<T>, class Alloc = std::allocator<T> > 
	class set
	{
	public:
		typedef T													key_type;
		typedef T													value_type;
		typedef Compare												key_compare;
		typedef Compare												value_compare;
		typedef Alloc												allocator_type;
		typedef typename allocator_type::reference					reference;
		typedef typename allocator_type::const_reference			const_reference;
		typedef typename allocator_type::pointer					pointer;
		typedef typename allocator_type::const_pointer				const_pointer;
		typedef ptrdiff_t											difference_type;
		typedef	size_t												size_type;
		typedef Tree<value_type, value_compare, allocator_type>		tree_type;
		typedef Node<value_type>									node_type;
		typedef	typename tree_type::const_iterator					iterator;
		typedef	typename tree_type::const_iterator					const_iterator;
		typedef	typename tree_type::const_reverse_iterator			reverse_iterator;
		typedef	typename tree_type::const_reverse_iterator			const_reverse_iterator;
		typedef typename allocator_type::template rebind<Tree<value_type, Compare, Alloc> >::other	tree_allocator; 
		typedef typename allocator_type::template rebind<Node<value_type> >::other					node_allocator; 
	private:
		tree_allocator	_tree_alloc;
		node_allocator	_node_alloc;
		allocator_type	_alloc;
		key_compare		_comp;
		tree_type		_tree;

	public:
// #######################################################################################
// Constructors, destructor, operator=
// #######################################################################################

		explicit set (const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()) :
		_alloc(alloc), _comp(comp), _tree(tree_type(comp, alloc)) { }

		template <class InputIterator>
		set (InputIterator first, InputIterator last,
			const key_compare& comp = key_compare(),
			const allocator_type& alloc = allocator_type()) :
			_alloc(alloc), _comp(comp), _tree(first, last, comp, alloc) { }

		set (const set& x) : _alloc(x._alloc), _comp(x._comp), _tree(x._tree) { }

		set& operator= (const set& x)
		{
			if (this != &x)
			{
				_alloc = x._alloc;
				_comp = x._comp;
				_tree = x._tree;
			}
			return *this;
		}

		virtual ~set() { }

// #######################################################################################
// Iterators
// #######################################################################################

		iterator begin() { return (_tree.begin()); }
		const_iterator begin() const { return (_tree.begin()); }
		iterator end() { return (_tree.end()); }
		const_iterator end() const { return (_tree.end()); }

		reverse_iterator rbegin() { return(_tree.rbegin()); }
		reverse_iterator rend() { return(_tree.rend()); }
		const_reverse_iterator rbegin() const { return(_tree.rbegin()); }
		const_reverse_iterator rend() const { return(_tree.rend()); }

// #######################################################################################
// Capacity
// #######################################################################################

		bool empty() const { return _tree.empty(); }
		size_type size() const { return _tree.size(); }
		size_type max_size() const
		{
			// return std::min<size_type> (_tree_alloc.max_size(), (std::numeric_limits<difference_type>::max() / sizeof(node_type)));
			return _node_alloc.max_size() + std::numeric_limits<difference_type>::max() / sizeof(node_type); // <- оно
			// return std::min<size_type> (_node_alloc.max_size(), (_node_alloc.max_size() + std::numeric_limits<difference_type>::max() / sizeof(node_type)));
			// return _alloc.max_size();
			// return std::min<size_type> (_node_alloc.max_size(), (std::numeric_limits<size_type>::max() / sizeof(node_type)));
		}

// #######################################################################################
// Modifiers
// #######################################################################################

		pair<iterator,bool> insert (const value_type& val) { return _tree.insert(val); }
		iterator insert (iterator position, const value_type& val) { return _tree.insert(position, val); }

		template <class InputIterator>
  		typename ft::enable_if< !ft::is_integral<InputIterator>::value, void>::type
		insert (InputIterator first, InputIterator last) { _tree.insert(first, last); }

		void erase(iterator pos) { _tree.erase(pos); }
		size_type erase(const value_type& val) { return (_tree.erase(val)); }
		void erase(iterator first, iterator last) { _tree.erase(first, last); }

		void swap (set& x)
		{
			ft::ft_swap(_alloc, x._alloc);
			ft::ft_swap(_comp, x._comp);
			_tree.swap(x._tree);
		}

		void clear() { _tree.clear(); }

// #######################################################################################
// Observers
// #######################################################################################

		key_compare key_comp() const { return _comp; }
		value_compare value_comp() const { return (_tree.value_comp()); }

// #######################################################################################
// Operations
// #######################################################################################

		iterator find(const value_type& val) { return _tree.find(val); }
		const_iterator find(const value_type& val) const { return _tree.find(val); }

		size_type count(const value_type& val) const { return find(val) != end(); }

		iterator lower_bound(const value_type& val) { return _tree.lower_bound(val); }
		const_iterator lower_bound(const value_type& val) const { return _tree.lower_bound(val); }

		iterator upper_bound(const value_type& val) { return _tree.upper_bound(val); }
		const_iterator upper_bound(const value_type& val) const { return _tree.upper_bound(val); }

		pair<const_iterator,const_iterator> equal_range(const value_type& val) const {
			return ft::make_pair(lower_bound(val), upper_bound(val));
		}
		pair<iterator,iterator> equal_range(const value_type& val) {
			return ft::make_pair(lower_bound(val), upper_bound(val));
		}

		allocator_type get_allocator() const { return _alloc; }

		friend bool operator==(const set<T, Compare, Alloc> & lhs, const set<T, Compare, Alloc> & rhs){
				return (lhs._tree == rhs._tree); 
		}
		friend bool operator<(const set<T, Compare, Alloc> & lhs, const set<T, Compare, Alloc> & rhs){
				return (lhs._tree < rhs._tree);
		}
	};
	
// #######################################################################################
// Non-member function overloads
// #######################################################################################

	template<class T, class Compare, class Alloc>
	bool operator!=(const set<T, Compare, Alloc> & lhs, const set<T, Compare, Alloc> & rhs){
			return !(lhs == rhs); 
	}

	template<class T, class Compare, class Alloc>
	bool operator>(const set<T, Compare, Alloc> & lhs, const set<T, Compare, Alloc> & rhs){
			return (rhs < lhs);
	}

	template<class T, class Compare, class Alloc>
	bool operator<=(const set<T, Compare, Alloc> & lhs, const set< T, Compare, Alloc> & rhs){
			return !(lhs > rhs);
	}

	template<class T, class Compare, class Alloc>
	bool operator>=(const set< T, Compare, Alloc> & lhs, const set< T, Compare, Alloc> & rhs){
			return !(lhs < rhs);
	}

	template <class T, class Compare, class Alloc>
  	void swap (set<T,Compare,Alloc>& x, set<T,Compare,Alloc>& y) { x.swap(y); }
}