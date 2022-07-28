#pragma once

#include "utils/utils.hpp"
#include "iterators/map_iterator.hpp"
#include "utils/Tree.hpp"
// #include <map>

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
		typedef Node<value_type>									node_type;
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
// Constructors & Destructor
// #######################################################################################

		explicit map (const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()) :
		_alloc(alloc), _comp(comp), _tree(tree_type(comp, alloc)) { }

		template <class InputIterator>
		map (InputIterator first, InputIterator last,
			const key_compare& comp = key_compare(),
			const allocator_type& alloc = allocator_type()) :
			_alloc(alloc), _comp(comp), _tree(first, last, comp, alloc) { }

		// map (const map& x) : _alloc(x._alloc), _comp(x._comp), _tree(x._tree) { }

		// ~map()
		// {

		// }

		mapped_type& operator[](const key_type& key){
			//make_pair(key, mapped_type());
		//	return	_tree.insert(make_pair(key, mapped_type())).first->second;
			return (*((this->insert(ft::make_pair(key, mapped_type()))).first)).second;
		}

		iterator begin(){
			return (_tree.begin());
		}

		const_iterator begin() const {
			return (_tree.begin());
		}

		iterator end(){
			return (_tree.end());
		}

		const_iterator end() const {
			return (_tree.end());
		}

		reverse_iterator rbegin(){
			return(_tree.rbegin());
		}

		reverse_iterator rend(){
			return(_tree.rend());
		}

		key_compare key_comp() const
		{
			return _comp;
		}

		value_compare value_comp() const{
			return (_tree.value_comp());
		}

		size_type size() const
		{
			return _tree.size();
		}

		size_type max_size() const
		{
			return _tree.max_size();
			// return std::min<size_type> (_tree_alloc.max_size(), (std::numeric_limits<difference_type >::max() / sizeof(node_type)));
		}

		pair<iterator,bool> insert (const value_type& val)
		{
			return _tree.insert(val);
		}

		void clear()
		{
			_tree.clear();
		}

		void erase(iterator pos){
			_tree.erase(pos);
		}

		size_type erase(const Key& key){
			return (_tree.erase(ft::make_pair(key, mapped_type())));
		}

		void erase(iterator first, iterator last){
			_tree.erase(first, last);
		}

		bool empty() const
		{
			return _tree.empty();
		}
	};
/*
	template<class Key, class T, class Compare, class Alloc>
	bool operator==(const map<Key, T, Compare, Alloc> & lhs, const map<Key, T, Compare, Alloc> & rhs){
			return (lhs._tree == rhs._tree); 
			lhs.
	}

	template<class Key, class T, class Compare, class Alloc>
	bool operator!=(const map<Key, T, Compare, Alloc> & lhs, const map<Key, T, Compare, Alloc> & rhs){
			return !(lhs == rhs); 
	}

	template<class Key, class T, class Compare, class Alloc>
	bool operator<(const map<Key, T, Compare, Alloc> & lhs, const map<Key, T, Compare, Alloc> & rhs){
			return (lhs._tree < rhs._tree);
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
	*/
}