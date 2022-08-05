#pragma once

#include "utils/utils.hpp"
#include "utils/Tree.hpp"

namespace ft
{
	template < class Key, class T, class Compare = std::less<Key>, class Alloc = std::allocator<pair<const Key,T> > >
	class map
	{
	public:
		typedef Key											key_type;
		typedef T											mapped_type;
		typedef pair<const key_type, mapped_type>			value_type;
		typedef Compare										key_compare;
		typedef Alloc										allocator_type;
		typedef typename allocator_type::reference			reference;
		typedef typename allocator_type::const_reference	const_reference;
		typedef typename allocator_type::pointer			pointer;
		typedef typename allocator_type::const_pointer		const_pointer;
		typedef ptrdiff_t									difference_type;
		typedef	size_t										size_type;
		typedef typename allocator_type::template rebind<Tree<value_type, Compare, Alloc> >::other	tree_allocator; 

	private:
		class value_compare {
			key_compare _compare;

			public:
				value_compare(const key_compare & compare) : _compare(compare) {}

				bool operator()(const value_type& x, const value_type& y) const{
					return (_compare(x.first, y.first));
				}
		};
	
	public:
		typedef Tree<value_type, value_compare, allocator_type>		tree_type;
		typedef ft::Node<value_type>								node_type;
		typedef	typename tree_type::iterator						iterator;
		typedef	typename tree_type::const_iterator					const_iterator;
		typedef	typename tree_type::reverse_iterator				reverse_iterator;
		typedef	typename tree_type::const_reverse_iterator			const_reverse_iterator;
	private:
		tree_allocator	_tree_alloc;
		allocator_type	_alloc;
		key_compare		_comp;
		tree_type		_tree;

	public:
// #######################################################################################
// Constructors, destructor, operator=
// #######################################################################################

		explicit map (const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()) :
		_alloc(alloc), _comp(comp), _tree(tree_type(comp, alloc)) { }

		template <class InputIterator>
		map (InputIterator first, InputIterator last,
			const key_compare& comp = key_compare(),
			const allocator_type& alloc = allocator_type()) :
			_alloc(alloc), _comp(comp), _tree(first, last, comp, alloc) { }

		map (const map& x) : _alloc(x._alloc), _comp(x._comp), _tree(x._tree) { }

		map& operator= (const map& x)
		{
			if (this != &x)
			{
				_alloc = x._alloc;
				_comp = x._comp;
				_tree = x._tree;
			}
			return *this;
		}

		virtual ~map() {}

// #######################################################################################
// Iterators
// #######################################################################################

		iterator begin() { return (_tree.begin()); }
		const_iterator begin() const { return (_tree.begin()); }
		iterator end() { return (_tree.end()); }
		const_iterator end() const { return (_tree.end()); }

		reverse_iterator rbegin() { return(_tree.rbegin()); }
		const_reverse_iterator rbegin() const { return(_tree.rbegin()); }
		reverse_iterator rend() { return(_tree.rend()); }
		const_reverse_iterator rend() const { return(_tree.rend()); }

// #######################################################################################
// Capacity
// #######################################################################################

		bool empty() const { return _tree.empty(); }
		size_type size() const { return _tree.size(); }

		size_type max_size() const
		{
			// return _tree.max_size();
			return std::min<size_type> (_tree_alloc.max_size(), (std::numeric_limits<difference_type>::max() / sizeof(value_type)));
			// return std::numeric_limits<difference_type>::max() / (sizeof(value_type) + sizeof(node_type));
		}

// #######################################################################################
// Element access
// #######################################################################################

		mapped_type& operator[](const key_type& key)
		{
			return (*((this->insert(ft::make_pair(key, mapped_type()))).first)).second;
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
		size_type erase(const Key& key) { return (_tree.erase(ft::make_pair(key, mapped_type()))); }
		void erase(iterator first, iterator last) { _tree.erase(first, last); }

		void swap (map& x)
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

		iterator find(const key_type& k) { return _tree.find(ft::make_pair(k, mapped_type()));}
		const_iterator find(const key_type& k) const { return _tree.find(ft::make_pair(k, mapped_type())); }

		size_type count(const key_type& k) const { return find(k) != end(); }

		iterator lower_bound(const key_type& k) { return _tree.lower_bound(ft::make_pair(k, mapped_type())); }
		const_iterator lower_bound(const key_type& k) const { return _tree.lower_bound(ft::make_pair(k, mapped_type())); }

		iterator upper_bound(const key_type& k) { return _tree.upper_bound(ft::make_pair(k, mapped_type())); }
		const_iterator upper_bound(const key_type& k) const { return _tree.upper_bound(ft::make_pair(k, mapped_type()));}

		pair<const_iterator,const_iterator> equal_range(const key_type& k) const {
			return ft::make_pair(lower_bound(k), upper_bound(k));
		}
		pair<iterator,iterator>	equal_range(const key_type& k) {
			return ft::make_pair(lower_bound(k), upper_bound(k));
		}

		allocator_type get_allocator() const { return allocator_type(); }

		friend bool operator==(const map<Key, T, Compare, Alloc> & lhs, const map<Key, T, Compare, Alloc> & rhs){
				return (lhs._tree == rhs._tree); 
		}

		friend bool operator<(const map<Key, T, Compare, Alloc> & lhs, const map<Key, T, Compare, Alloc> & rhs){
				return (lhs._tree < rhs._tree);
		}
	};

	template<class Key, class T, class Compare, class Alloc>
	bool operator!=(const map<Key, T, Compare, Alloc> & lhs, const map<Key, T, Compare, Alloc> & rhs){
			return !(lhs == rhs); 
	}


	template<class Key, class T, class Compare, class Alloc>
	bool operator>(const map<Key, T, Compare, Alloc> & lhs, const map<Key, T, Compare, Alloc> & rhs){
			return (rhs < lhs);
	}

	template<class Key, class T, class Compare, class Alloc>
	bool operator<=(const map<Key, T, Compare, Alloc> & lhs, const map<Key, T, Compare, Alloc> & rhs){
			return !(lhs > rhs);
	}

	template<class Key, class T, class Compare, class Alloc>
	bool operator>=(const map<Key, T, Compare, Alloc> & lhs, const map<Key, T, Compare, Alloc> & rhs){
			return !(lhs < rhs);
	}

	template <class Key, class T, class Compare, class Alloc>
  	void swap (map<Key,T,Compare,Alloc>& x, map<Key,T,Compare,Alloc>& y)
	{
		x.swap(y);
	}
}