/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmunoz-f <mmunoz-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 16:32:30 by mmunoz-f          #+#    #+#             */
/*   Updated: 2021/10/13 16:56:30 by mmunoz-f         ###   ########.fr       */
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

		private:

			Container	c;

	};

}


#endif
