#pragma once

#include "../iterators/node_iterator.hpp"
#include "../iterators/reverse_iterator.hpp"
#include "../utils/utils.hpp"

#define RED		false
#define BLACK	true

template < class Val, class Compare = std::less<Val>, class Alloc = std::allocator<Val> >
class Tree
{
public:
	typedef Val																			value_type;
	typedef Compare																		val_compare;
	typedef Alloc																		allocator_type;
	typedef typename allocator_type::template rebind<Node<value_type> >::other			node_allocator;
	typedef typename allocator_type::template rebind<Tree<Val, Compare, Alloc> >::other	tree_allocator;
	// typedef Node<value_type>*															node_pointer;
	typedef typename node_allocator::pointer															node_pointer;
	typedef typename allocator_type::reference											reference;
	typedef typename allocator_type::const_reference									const_reference;
	typedef typename allocator_type::pointer											pointer;
	typedef typename allocator_type::const_pointer										const_pointer;
	typedef ptrdiff_t																	difference_type;
	typedef	size_t																		size_type;
	typedef ft::node_iterator<value_type>												iterator;
	typedef ft::node_iterator<const value_type>											const_iterator;
	typedef ft::reverse_iterator<iterator>												reverse_iterator;
	typedef ft::reverse_iterator<const_iterator>										const_reverse_iterator;
private:
	allocator_type	_alloc_val;
	node_allocator	_alloc_node;
	tree_allocator	_alloc_tree;
	val_compare		_comp;
	node_pointer	_nil;
	node_pointer	_end;
	node_pointer	_root;
	size_type		_size;
	// size_type		_max_size;

// #######################################################################################
// private methods:
// #######################################################################################

	void _init()
	{
		// _max_size = std::min<size_type> (_alloc_tree.max_size(), (std::numeric_limits<difference_type >::max() / sizeof(value_type)));

		_nil = _alloc_node.allocate(1);
		_alloc_node.construct(_nil, Node<value_type>());
		_nil->_isRed = false;
		_nil->_isNil = true;
		_end = _alloc_node.allocate(1);
		_alloc_node.construct(_end, Node<value_type>());
		_end->_val = _alloc_val.allocate(1);
		_alloc_val.construct(_end->_val, value_type());
		_end->_isRed = false;
	}

	bool _is_nil(node_pointer node) const
	{
		return node == _nil || node == _end;
	}

	// ——————————————————————————————————————————————————————————————————————
	// Min & Max
	// ——————————————————————————————————————————————————————————————————————
	
	node_pointer	_tree_min(node_pointer n) const
	{
		while (n != NULL && n->_left != _nil)
			n = n->_left;
		return n;
	}

	node_pointer	_tree_max(node_pointer n) const
	{
		while (n != NULL && !_is_nil(n->_right))
			n = n->_right;
		return n;
	}

	// ——————————————————————————————————————————————————————————————————————
	// Create val, Copy node, Clear node, Copy child
	// ——————————————————————————————————————————————————————————————————————

	pointer _create_val(const value_type& val)
	{
		pointer tmp = _alloc_val.allocate(1);
		_alloc_val.construct(tmp, val);
		return tmp;
	}

	void _clear_node(node_pointer node)
	{
		if (node && !_is_nil(node)) {
			_clear_node(node->_right);
			_clear_node(node->_left);
			_alloc_val.destroy(node->_val);
			_alloc_val.deallocate(node->_val, 1);
			_alloc_node.deallocate(node, 1);
		}
	}

	node_pointer _copy_node(node_pointer other)
	{
		node_pointer tmp = _alloc_node.allocate(1);
		_alloc_node.construct(tmp, Node<Val>());
		tmp->_isNil = other->_isNil;
		tmp->_isRed = other->_isRed;
		if (other->_val)
		{
			tmp->_val = _alloc_val.allocate(1);
			_alloc_val.construct(tmp->_val, *other->_val);
		}
		return tmp;
	}

	void _copy_child(node_pointer dest, node_pointer other)
	{
		if (other->_left->_isNil)
			dest->_left = _nil;
		else
		{
			dest->_left = _copy_node(other->_left);
			dest->_left->_parent = dest;
			_copy_child(dest->_left, other->_left);
		}
		if (other->_right->_isNil)
			dest->_right = _nil;
		else if (other->_right->_right == NULL)
		{
			dest->_right = _end;
			_end->_parent = dest;
		}
		else
		{
			dest->_right = _copy_node(other->_right);
			dest->_right->_parent = dest;
			_copy_child(dest->_right, other->_right);
		}
	}

	// ——————————————————————————————————————————————————————————————————————
	// Find node & Insert
	// ——————————————————————————————————————————————————————————————————————

	node_pointer _find_node(const value_type& val, node_pointer node) const
	{
		if (!node || _is_nil(node))
			return NULL;
		if (_comp(val, *node->_val))
			return _find_node(val, node->_left);
		if (_comp(*node->_val, val))
			return _find_node(val, node->_right);
		return node;
	}

	node_pointer _insert_node(node_pointer node, node_pointer root)
	{
		if (_comp(*node->_val, *root->_val))
		{
			if (!_is_nil(root->_left))
				return _insert_node(node, root->_left);
			root->_left = node;
		}
		else
		{
			if (!_is_nil(root->_right))
				return _insert_node(node, root->_right);
			root->_right = node;
		}
		node->_parent = root;
		return node;
	}

	void _insert_into_tree(node_pointer node, node_pointer where)
	{
		if (where == _end)
			_root = node;
		else
			_insert_node(node, where);
	}

	// ——————————————————————————————————————————————————————————————————————
	// Rotate
	// ——————————————————————————————————————————————————————————————————————

	void _rotate_left(node_pointer node)
	{
		node_pointer tmp = node->_right;
		node->_right = tmp->_left;
		if (!(_is_nil(tmp->_left)))
			tmp->_left->_parent = node;
		tmp->_parent = node->_parent;
		if (node->_parent == NULL)
			_root = tmp;
		else if (node->_parent->_left == node)
			node->_parent->_left = tmp;
		else
			node->_parent->_right = tmp;
		tmp->_left = node;
		node->_parent = tmp;
	}

	void _rotate_right(node_pointer node)
	{
		node_pointer tmp = node->_left;
		node->_left = tmp->_right;
		if (!(_is_nil(tmp->_right)))
			tmp->_right->_parent = node;
		tmp->_parent = node->_parent;
		if (node->_parent == NULL)
			_root = tmp;
		else if (node->_parent->_right == node)
			node->_parent->_right = tmp;
		else
			node->_parent->_left = tmp;
		tmp->_right = node;
		node->_parent = tmp;

	}

	// ——————————————————————————————————————————————————————————————————————
	// Balance after insert
	// ——————————————————————————————————————————————————————————————————————

	void _balance_after_insert(node_pointer node)
	{
		while (node != _root && node->_parent->_isRed)
		{
			if (node->_parent == node->_parent->_parent->_left)
			{
				node_pointer uncle = node->_parent->_parent->_right;
				if (uncle->_isRed)
				{
					node->_parent->_isRed = false;
					uncle->_isRed = false;
					node->_parent->_parent->_isRed = true;
					node = node->_parent->_parent;
				}
				else 
				{
					if (node == node->_parent->_right)
					{
						node = node->_parent;
						_rotate_left(node);
					}
					node->_parent->_isRed = false;
					node->_parent->_parent->_isRed = true;
					_rotate_right(node->_parent->_parent);
				}
			}
			else
			{
				node_pointer uncle = node->_parent->_parent->_left;
				if (uncle->_isRed)
				{
					node->_parent->_isRed = false;
					uncle->_isRed = false;
					node->_parent->_parent->_isRed = true;
					node = node->_parent->_parent;
				}
				else 
				{
					if (node == node->_parent->_left)
					{
						node = node->_parent;
						_rotate_right(node);
					}
					node->_parent->_isRed = false;
					node->_parent->_parent->_isRed = true;
					_rotate_left(node->_parent->_parent);
				}
			}
		}
		_root->_isRed = false;
	}
	// node_pointer _balance_after_insert(node_pointer node)
	// {
	// 	if (node != _root)
	// 	{
	// 		if (!node->_parent->_isRed)
	// 			return node;
	// 		if (node->_parent->_parent->_left == node->_parent)
	// 		{
	// 			node_pointer uncle = node->_parent->_parent->_right;
	// 			if (uncle->_isRed)
	// 			{
	// 				node->_parent->_isRed = false;
	// 				uncle->_isRed = false;
	// 				node->_parent->_parent->_isRed = true;
	// 				return _balance_after_insert(node->_parent->_parent);
	// 			}
	// 			else
	// 			{
	// 				if (node->_parent->_right == node)
	// 				{
	// 					node = node->_parent;
	// 					_rotate_left(node);
	// 				}
	// 				_rotate_right(node->_parent->_parent);
	// 				node->_parent->_right->_isRed = true;
	// 				node->_parent->_isRed = false;
	// 				return node;
	// 			}
	// 		}
	// 		else
	// 		{
	// 			node_pointer uncle = node->_parent->_parent->_left;
	// 			if (uncle->_isRed)
	// 			{
	// 				node->_parent->_isRed = false;
	// 				uncle->_isRed = false;
	// 				node->_parent->_parent->_isRed = true;
	// 				return _balance_after_insert(node->_parent->_parent);
	// 			}
	// 			else
	// 			{
	// 				if (node->_parent->_left == node)
	// 				{
	// 					node = node->_parent;
	// 					_rotate_right(node);
	// 				}
	// 				_rotate_left(node->_parent->_parent);
	// 				node->_parent->_left->_isRed = true;
	// 				node->_parent->_isRed = false;
	// 				return node;
	// 			}
	// 		}
	// 	}
	// 	_root->_isRed = false;
	// 	return node;
	// }

public:

// #######################################################################################
// Constructors, destructor, operator=
// #######################################################################################

	Tree() : _alloc_val(allocator_type()), _alloc_node(node_allocator()), _comp(val_compare()), _root(NULL), _size(0)
	{
		_init();
		_root = _end;

	}

	Tree(const Tree& other) : _comp(other._comp), _root(NULL)
	{
		*this = other;
	}

	Tree(const val_compare& comp = val_compare(), const allocator_type& alloc = allocator_type()) :
			_alloc_val(alloc), _alloc_node(node_allocator()), _comp(comp), _root(NULL), _size(0)
	{
		_init();
		_root = _end;
	}

	template <class InputIterator>
	Tree(InputIterator first, InputIterator last,
			const val_compare& comp = val_compare(), const allocator_type& alloc = allocator_type(),
			typename ft::enable_if< !ft::is_integral<InputIterator>::value, void>::type* = 0) :
			_alloc_val(alloc), _alloc_node(node_allocator()), _comp(comp), _root(NULL), _size(0)
	{
		_init();
		_root = _end;
		for (; first != last; ++first)
			insert(*first);
	}

	Tree& operator=(const Tree& other)
	{
		if (this != &other)
		{
			_alloc_val = other._alloc_val;
			_alloc_node = other._alloc_node;
			_comp = other._comp;
			if (_root == NULL)
				_init();
			else
				_clear_node(this->_root);
			if (other._size == 0)
				_root = _end;
			else
			{
				_root = _copy_node(other._root);
				_copy_child(_root, other._root);
			}
			_size = other._size;
		}
		return *this;
	}

	~Tree()
	{
		_clear_node(_root);
		_alloc_val.destroy(_end->_val);
		_alloc_val.deallocate(_end->_val, 1);
		_alloc_node.deallocate(_nil, 1);
		_alloc_node.deallocate(_end, 1);
	}

// #######################################################################################
// Iterators
// #######################################################################################

	iterator	begin()
	{
		return (iterator(_size == 0 ? _end : iterator(_tree_min(_root))));
	}

	const_iterator	begin() const
	{
		return (const_iterator(_size == 0 ? _end : const_iterator(_tree_min(_root))));
	}

	iterator	end()
	{
		return iterator(_end);
	}

	const_iterator	end() const
	{
		return const_iterator(_end);
	}

	reverse_iterator rbegin()
	{
		return (reverse_iterator(end()));
	}

	const_reverse_iterator rbegin() const
	{
		return (const_reverse_iterator(end()));
	}	

	reverse_iterator rend()
	{
		return (reverse_iterator(begin()));
	}	

	const_reverse_iterator rend() const
	{
		return (const_reverse_iterator(begin()));
	}

// #######################################################################################
// Capacity:
// #######################################################################################

	bool empty() const
	{
		return _size == 0;
	}

	size_type size() const
	{
		return _size;
	}

	size_type max_size() const
	{
		return std::min<difference_type> (_alloc_tree.max_size(), (std::numeric_limits<difference_type>::max() / sizeof(value_type)));
	}

// #######################################################################################
// Modifiers:
// #######################################################################################

	ft::pair<iterator, bool> insert (const value_type& val)
	{
		node_pointer newNode = _find_node(val, _root);
		if (newNode)
			return ft::pair<iterator, bool>(iterator(newNode), false);
		newNode = _alloc_node.allocate(1);
		_alloc_node.construct(newNode, Node<value_type>(_create_val(val)));
		newNode->_left = _nil;
		newNode->_right = _nil;
		_insert_into_tree(newNode, _root);
		ft::pair<iterator, bool> ret(iterator(newNode), true);
		_balance_after_insert(newNode);
		_size++;
		// newNode = _tree_max(_root);
		_end->_parent = _tree_max(_root);
		_end->_parent->_right = _end;
		return ret;
	}

	iterator insert (const_iterator position, const value_type& val)
	{
		node_pointer newNode = _find_node(val, _root);
		if (newNode)
			return iterator(newNode);
		newNode = _alloc_node.allocate(1);
		_alloc_node.construct(newNode, Node<value_type>(_create_val(val)));
		newNode->_left = _nil;
		newNode->_right = _nil;
		if (position == begin())
		{
			if (position != end() && _comp(val, *position))
				_insert_into_tree(newNode, _tree_min(_root));
			else
				_insert_into_tree(newNode, _root);
		}
		else if (position == end())
		{
			if (position != begin() && _comp(*(--position), val))
				_insert_into_tree(newNode, _end->_parent);
			else
				_insert_into_tree(newNode, _root);
		}
		else
		{
			if (_comp(val, *(position)))
				_insert_into_tree(newNode, (--position).iter());
			else
				_insert_into_tree(newNode, _root);
		}
		_balance_after_insert(newNode);
		_size++;
		// node_pointer tmp = _tree_max(_root);
		_end->_parent = _tree_max(_root);
		_end->_parent->_right = _end;
		return iterator(newNode);
	}

	template <class InputIterator>
	typename ft::enable_if< !ft::is_integral<InputIterator>::value, void>::type
	insert (InputIterator first, InputIterator last)
	{
		for (; first != last; ++first)
		{
			// insert(ft::make_pair(first->first, first->second));
			insert(*first);
		}
		
	}

	void swap(Tree &x)
	{
		ft::ft_swap(_alloc_val, x._alloc_val);
		ft::ft_swap(_alloc_node, x._alloc_node);
		ft::ft_swap(_alloc_tree, x._alloc_tree);
		ft::ft_swap(_comp, x._comp);
		ft::ft_swap(_nil, x._nil);
		ft::ft_swap(_end, x._end);
		ft::ft_swap(_root, x._root);
		ft::ft_swap(_size, x._size);
	}

	void clear()
	{
		_clear_node(_root);
		_root = _end;
		_end->_parent = NULL;
		_size = 0;
	}

	void transplant(node_pointer where, node_pointer what) {
			if (where == _root)
				_root = what;
			else if (where == where->_parent->_left)
				where->_parent->_left = what;
			else
				where->_parent->_right = what;
			what->_parent = where->_parent;
		}

	void 	free_node(node_pointer node){
			_alloc_val.destroy(node->_val);
			_alloc_val.deallocate(node->_val, 1);
			_alloc_node.deallocate(node, 1);
		}


	void erase_fixup(node_pointer x){
		node_pointer brother;
		while (x != _root && !x->_isRed)
		{
			if (x == x->_parent->_left)
			{
				brother = x->_parent->_right;
				if (brother->_isRed)
				{
					brother->_isRed = false;
					x->_parent->_isRed = true;
					_rotate_left(x->_parent);
					brother = x->_parent->_right;
				}
				if (!brother->_left->_isRed && !brother->_right->_isRed)
				{
					brother->_isRed = true;
					x = x->_parent;
				}
				else
				{
					if (!brother->_right->_isRed)
					{
						brother->_left->_isRed = false;
						brother->_isRed = true;
						_rotate_right(brother);
						brother = x->_parent->_right;
					}
					brother->_isRed = x->_parent->_isRed;
					x->_parent->_isRed = false;
					brother->_right->_isRed = false;
					_rotate_left(x->_parent);
					x = _root;
				}
			}
			else
			{
				brother = x->_parent->_left;
				if (brother->_isRed)
				{
					brother->_isRed = false;
					x->_parent->_isRed = true;
					_rotate_right(x->_parent);
					brother = x->_parent->_left;
				}
				if (!brother->_left->_isRed && !brother->_left->_isRed)
				{
					brother->_isRed = true;
					x = x->_parent;
				}
				else
				{
					if (!brother->_left->_isRed)
					{
						brother->_left->_isRed = false;
						brother->_isRed = true;
						_rotate_left(brother);
						brother = x->_parent->_left;
					}
					brother->_isRed = x->_parent->_isRed;
					x->_parent->_isRed = false;
					brother->_left->_isRed = false;
					_rotate_right(x->_parent);
					x = _root;
				}
			}
		}
		x->_isRed = false;
	}

	void erase(const_iterator pos){
			node_pointer y = pos.iter(), x, z = y , for_free = y;
			bool y_original_is_red = y->_isRed;
			if (_is_nil(z->_left)){
				x = z->_right;
				transplant(z, z->_right);
			}
			else if (_is_nil(z->_right)){
				x = z->_left;
				transplant(z, z->_left);
			}
			else {
				y = _tree_min(z->_right);
				y_original_is_red = y->_isRed;
				x = y->_right;
				if (y->_parent == z){
					x->_parent = y;
				}
				else
				{
					transplant(y, y->_right);
					y->_right = z->_right;
					y->_right->_parent = y;
				}
				transplant(z, y);
				y->_left = z->_left;
				y->_left->_parent = y;
				y->_isRed = z->_isRed;
			}
			free_node(for_free);
			if (!y_original_is_red)
				erase_fixup(x);
			_size--;
			_nil->_parent = NULL;
			if (_size == 0)
				_root = _end;
			else
			{
				if (_size != 1)
					x = _tree_max(_root);
				else
					x = _root;
				x->_right = _end;
				_end->_parent = x;
			}
		}

		size_type erase(const value_type& value){
			node_pointer res = _find_node(value, _root);
			if (res)
				erase(iterator(res));
			return (res != NULL);
		}

		void erase(const_iterator first, const_iterator last){
			while (first != last)
				erase(first++);
		}

		val_compare value_comp() const {
			return (_comp);
		}

		iterator find(const value_type& k)
		{
			node_pointer ret = _find_node(k, _root);
			return ret == NULL ? end() : iterator(ret);
		}

		const_iterator find(const value_type& k) const
		{
			node_pointer ret = _find_node(k, _root);
			return ret == NULL ? end() : const_iterator(ret);
		}

		iterator lower_bound(const value_type& k)
		{
			Node<value_type> *current = _root;

			while (!_is_nil(current)) {
				// if (k.first == current->_val->first)
				if (!_comp(k, *current->_val) && !_comp(*current->_val, k))
					return iterator(current);
				else {
					if (_comp(k, *(current->_val))) {
						if (!current->_left->_isNil)
							current = current->_left;
						else
							return iterator(current);
					}
					else {
						if (!current->_right->_isNil)
							current = current->_right;
						else
							return ++iterator(current);
					}
				}
			}
			return end();
		}

		const_iterator lower_bound(const value_type& k) const
		{
			node_pointer current = _root;

			while (!_is_nil(current)) {
				// if (k.first == current->_val->first)
				if (!_comp(k, *current->_val) && !_comp(*current->_val, k))
					return const_iterator(current);
				else {
					if (_comp(k, *(current->_val))) {
						if (!current->_left->_isNil)
							current = current->_left;
						else
							return const_iterator(current);
					}
					else {
						if (!current->_right->_isNil)
							current = current->_right;
						else
							return ++const_iterator(current);
					}
				}
			}
			return end();
		}

		iterator upper_bound(const value_type& k)
		{
			iterator ret = lower_bound(k);

			if (ret == end() || _comp(k, *ret))
				return ret;
			return ++ret;
		}

		const_iterator upper_bound(const value_type& k) const
		{
			const_iterator ret = lower_bound(k);

			if (ret == end() || _comp(k, *ret))
				return ret;
			return ++ret;
		}
	
};

template<class Content, class Compare, class Alloc>
bool operator<(const Tree<Content, Compare, Alloc>& lhs,  const Tree<Content, Compare, Alloc>& rhs){
	return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
}

template<class Content, class Compare, class Alloc>
bool operator==(const Tree<Content, Compare, Alloc>& lhs, const Tree<Content, Compare, Alloc>& rhs){
	return (lhs.size() == rhs.size() && ft::equal(lhs.begin(), lhs.end(), rhs.begin()));
}