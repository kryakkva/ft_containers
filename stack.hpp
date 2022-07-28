#ifndef STACK_HPP
# define STACK_HPP

# include "vector.hpp"

namespace ft
{
	template <class T, class Container = ft::vector<T> >
	class stack
	{
		public:
			typedef T			value_type;
			typedef Container	container_type;
			typedef size_t		size_type;

			explicit stack(const container_type & container = container_type()) { c = container; }

			~stack () {}
			size_type size() const { return (c.size()); }
			bool empty() const { return (c.empty()); }
			value_type& top() { return(c.back()); }
			const value_type& top() const { return(c.back()); }
			void push (const value_type& val) { c.push_back(val); }
			void pop() { c.pop_back(); }
		protected:
			container_type c;
		private:
			friend bool operator== (const stack &lhs, const stack &rhs) { return (lhs.c == rhs.c); }
			friend bool operator< (const stack &lhs, const stack &rhs) { return (lhs.c < rhs.c); }
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
#endif