// #ifndef STACK_HPP
// # define STACK_HPP
#pragma once

# include <vector>

namespace ft
{
	template <class T, class Container = std::vector<T> >
	class stack
	{
		public:
			typedef T			value_type;
			typedef Container	container_type;
			typedef size_t		size_type;

			explicit stack(const container_type & container = container_type()) { _container = container; }
			~stack () {}
			size_type size() const { return (_container.size()); }
			bool empty() const { return (_container.empty()); }
			value_type& top() { return(_container.back()); }
			const value_type& top() const { return(_container.back()); }
			void push (const value_type& val) { _container.push_back(val); }
			void pop() { _container.pop_back(); }
		private:
			container_type _container;
			friend bool operator== (const stack &lhs, const stack &rhs) { return (lhs._container == rhs._container); }
			friend bool operator< (const stack &lhs, const stack &rhs) { return (lhs._container < rhs._container); }
	};

template <class T, class Container>
bool operator!= (const stack<T,Container>& lhs, const stack<T,Container>& rhs) { return (!(lhs == rhs)); }

template <class T, class Container>
bool operator>  (const stack<T,Container>& lhs, const stack<T,Container>& rhs) { return ((rhs < lhs)); }

template <class T, class Container>
bool operator<= (const stack<T,Container>& lhs, const stack<T,Container>& rhs) { return (!(rhs < lhs)); }

template <class T, class Container>
bool operator>= (const stack<T,Container>& lhs, const stack<T,Container>& rhs) { return (!(lhs < rhs)); }

}
// #endif