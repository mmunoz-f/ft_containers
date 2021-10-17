/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miguel <miguel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 16:32:30 by mmunoz-f          #+#    #+#             */
/*   Updated: 2021/10/17 04:28:23 by miguel           ###   ########.fr       */
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

			reference	top() { return (c.back()); }
			const_reference	top() const { return (c.back()); }

			bool	empty() const { return (c.empty()); }

			size_type	size() const {return (c.size()); }

			void	push(const value_type &value) { c.push_back(value); }
			void	pop() { c.pop_back(); }

			void	swap(stack &other) { ft::vector<T>::swap(c, other.c); }

		private:

			Container	c;

	};

}


#endif
