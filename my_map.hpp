#pragma once

#include "utils.hpp"
#include "RbTree.hpp"
// #include <map>

namespace ft
{
	template < class Key, class T, class Compare = std::less<Key>, class Alloc = std::allocator<pair<const Key,T> > >
	class map
	{
	private:
		struct Node;
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
		typedef Node*										node_pointer;
		typedef ptrdiff_t									difference_type;
		typedef	size_t										size_type;

	private:
		struct Node
		{
			bool			isRed;
			bool			isNill;
			value_type 		_val;
			node_pointer	_parent;
			node_pointer	_left;
			node_pointer	_right;
		};


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
		typedef RbTree<value_type, value_compare, allocator_type>	tree_type;
		typedef	typename tree_type::iterator						iterator;
		typedef	typename tree_type::const_iterator					const_iterator;
		typedef	typename tree_type::reverse_iterator				reverse_iterator;
		typedef	typename tree_type::const_reverse_iterator			const_reverse_iterator;
	private:
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

		map (const map& x);

		~map()
		{

		}

	};
}