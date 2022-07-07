#pragma once

#include "utils.hpp"
#include "map_iterator.hpp"

#define RED		false
#define BLACK	true

template <class value_type>
struct Node
{
	public:
	explicit Node(value_type* other = NULL) :
			_isRed(true), _isNill(false), _parent(NULL), _left(NULL), _right(NULL), _val(other) {}

	bool		_isRed;
	bool		_isNill;
	Node* 		_parent;
	Node*		_left;
	Node*		_right; 
	value_type*	_val;

	Node(const Node& other) { *this = other; }

	Node& operator=(const Node& other)
	{
		_isRed = other._isRed;
		_isNill = other._isNill;
		_parent = other._parent;
		_left = other._left;
		_right = other._right;
		_val = other._val;
		return *this;
	}

	virtual ~Node() {}
};


template < class Val, class Compare = std::less<Val>, class Alloc = std::allocator<Val> >
class RbTree
{
public:
	typedef Val																		value_type;
	typedef Compare																	val_compare;
	typedef Alloc																	allocator_type;
	typedef typename allocator_type::template rebind<Node<value_type> >::other		node_allocator;
	typedef Node<value_type>*														node_pointer;
	typedef typename allocator_type::reference										reference;
	typedef typename allocator_type::const_reference								const_reference;
	typedef typename allocator_type::pointer										pointer;
	typedef typename allocator_type::const_pointer									const_pointer;
	typedef ptrdiff_t																difference_type;
	typedef	size_t																	size_type;
	// typedef map_iterator<Val, false>												iterator;
	// typedef map_iterator<Val, true>													const_iterator;
private:
	allocator_type	_alloc_val;
	node_allocator	_alloc_node;
	val_compare		_comp;
	node_pointer	_root;
	node_pointer	_end;
	node_pointer	_nil;
	size_type		_size;

// #######################################################################################
// private methods:
// #######################################################################################

	void _init()
	{
		_nil = _alloc_node.allocate(1);
		_alloc_node.construct(_nil, Node<value_type>());
		_nil->isRed = false;
		_nil->isNil = true;
		_end = _alloc_node.allocate(1);
		_alloc_node.construct(_end, Node<value_type>());
		_end->isRed = false;
	}

	bool _is_nil(node_pointer node) const
	{
		return node == _nil || node == _end;
	}

	node_pointer _find_node(const value_type& val, node_pointer node)
	{
		if (!node || _is_nil(node));
			return NULL;
		if (_comp(val, *node->_val))
			_find_node(val, node->_left);
		if (_comp(*node->_val, val))
			_find_node(val, node->_right);
		return node;
	}

	pointer _create_val(const value_type& val)
	{
		pointer tmp = _alloc_val.allocate(1);
		_alloc_val.construct(tmp, val);
		return tmp;
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

	void balance_after_insert(node_pointer node)
	{
		if (node != _root)
		{

		}
		node->_isRed = false;
	}
	
public:
	// RbTree() : _root(NULL), _size(0), _comp(val_compare()), _alloc_val(allocator_type()), _alloc_node(node_allocator())
	// {
	// 	_init();
	// 	_root = _end;
	// }

// #######################################################################################
// Constructors & Destructor
// #######################################################################################

	RbTree(const val_compare& comp = val_compare(), const allocator_type& alloc = allocator_type()) :
			_root(NULL), _size(0), _comp(comp), _alloc_val(alloc), _alloc_node(node_allocator())
	{
		_init();
		_root = _end;
	}

	template <class InputIterator>
	RbTree(InputIterator first, InputIterator last,
			const val_compare& comp = val_compare(), const allocator_type& alloc = allocator_type(),
			typename ft::enable_if< !ft::is_integral<InputIt>::value, InputIt >::type = 0)
	{
		_init();
		_root = _end;
		for (; first != last; ++first)
			insert(*first);
	}

// #######################################################################################
// Modifiers:
// #######################################################################################

	// ——————————————————————————————————————————————————————————————————————
	// Assign
	// ——————————————————————————————————————————————————————————————————————

	ft::pair<iterator, bool> insert (const value_type& val)
	{
		node_pointer tmp = _find_node(val, _root);
		if (tmp)
			return ft::pair<iterator, bool>(iterator(tmp), false);
		node_pointer newNode = _alloc_node.allocate(1);
		_alloc_node.construct(newNode, Node<value_type>(_create_val(val)));
		newNode->_left = _nil;
		newNode->_right = _nil;
		_insert_into_tree(newNode, _root);
	}

	iterator insert (iterator position, const value_type& val);

	template <class InputIterator>
	void insert (InputIterator first, InputIterator last);
	
};
