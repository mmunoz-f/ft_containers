/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmunoz-f <mmunoz-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/17 16:59:50 by mmunoz-f          #+#    #+#             */
/*   Updated: 2021/10/17 18:51:10 by mmunoz-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __MAP_H__
# define __MAP_H__

# include <functional>
# include <memory>
# include "utils/pair.hpp"
# include "utils/reverse_iterator.hpp"
# include "utils/red_black_tree.hpp"

namespace ft {

	template<class T>
	class	map_iterator {

	};

	template<class Key, class T, class Compare = std::less<Key>, class Allocator = std::allocator<ft::pair<const Key, T> > >
	class	map {

		public:
			typedef Key										key_type;
			typedef T										mapped_type;
			typedef ft::pair<const Key, T>					value_type;
			typedef std::size_t								size_type;
			typedef std::ptrdiff_t							difference_type;
			typedef Compare									key_compare;

			typedef Allocator								allocator_type;
			typedef typename Allocator::reference			reference;
			typedef typename Allocator::const_reference		const_reference;
			typedef typename Allocator::pointer				pointer;
			typedef typename Allocator::const_pointer		const_pointer;

			typedef map_iterator<pointer>					iterator;
			typedef map_iterator<const_pointer>				const_iterator;
			typedef ft::reverse_iterator<iterator>			reverse_iterator;
			typedef ft::reverse_iterator<const_iterator>	const_reverse_iterator;

			class	value_compare {
				protected:
					key_compare	comp;
				public:
					typedef bool		result_type;
					typedef value_type	first_argument_type;
					typedef value_type	second_argument_type;

					value_compare(key_compare c) : comp(c) {}

					bool	operator()(const value_type &lhs, const value_type &rhs) const { return (comp(lhs.first, rhs.first)); }
			};

			/* CONSTRUCTORS */

			map() : value_compare(Compare()), _tree(value_compare, Allocator()) {}
			explicit	map(const Compare &comp, const Allocator &alloc = Allocator()) :  {}
			/* --------- */

		private:
			ft::tree<value_type, value_compare, allocator_type>	_tree;
	};
}

#endif
