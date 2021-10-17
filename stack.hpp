/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmunoz-f <mmunoz-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 16:32:30 by mmunoz-f          #+#    #+#             */
/*   Updated: 2021/10/17 16:57:19 by mmunoz-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __STACK_H__
# define __STACK_H__

# include "vector.hpp"

namespace ft {

	template<class T, class Container = ft::vector<T> >
	class	stack {

		public:

			typedef Container							container_type;
			typedef typename Container::value_type		value_type;
			typedef typename Container::size_type		size_type;
			typedef typename Container::reference		reference;
			typedef typename Container::const_reference	const_reference;

			/* CONSTRUCTOR */

			explicit stack(const Container &cont = Container()) : c(cont) {}
			stack(const stack &other) : c(other.c) {}
			/* --------- */

			/* DESTRUCTOR */

			~stack() {}
			/* --------- */

			/* DESTRUCTOR */

			stack&	operator=(const stack &other) {
				if (this == &other)
					return;
				c = other.c;
			}
			/* --------- */

			reference		top() { return (c.back()); }
			const_reference	top() const { return (c.back()); }

			bool	empty() const { return (c.empty()); }

			size_type	size() const {return (c.size()); }

			void	push(const value_type &value) { c.push_back(value); }
			void	pop() { c.pop_back(); }

			template<class U, class Cont>
			friend bool	operator==(const stack<U, Cont> &lhs, const stack<U, Cont> &rhs);
			template<class U, class Cont>
			friend bool	operator<(const stack<U, Cont> &lhs, const stack<U, Cont> &rhs);

			template<class U, class Cont>
			friend void	swap(stack<U, Cont> &lhs, stack<U, Cont>& rhs);

		private:

			Container	c;

	};

	template<class T, class Container>
	bool	operator==(const stack<T,Container> &lhs, const stack<T,Container> &rhs) { return (lhs.c == rhs.c); }
	template<class T, class Container>
	bool	operator!=(const stack<T,Container> &lhs, const stack<T,Container> &rhs) { return !(lhs == rhs); }
	template<class T, class Container>
	bool	operator<(const stack<T,Container> &lhs, const stack<T,Container> &rhs) { return (lhs.c < rhs.c); }
	template<class T, class Container>
	bool	operator<=(const stack<T,Container> &lhs, const stack<T,Container> &rhs) { return !(rhs < lhs); }
	template<class T, class Container>
	bool	operator>(const stack<T,Container> &lhs, const stack<T,Container> &rhs) { return (rhs < lhs); }
	template<class T, class Container>
	bool	operator>=(const stack<T,Container> &lhs, const stack<T,Container> &rhs) { return !(lhs < rhs); }

	template<class T, class Container>
	void	swap(stack<T,Container> &lhs, stack<T,Container>& rhs) { lhs.c.swap(rhs.c); }
}

#endif
