/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmunoz-f <mmunoz-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/17 16:59:50 by mmunoz-f          #+#    #+#             */
/*   Updated: 2021/11/18 15:13:25 by mmunoz-f         ###   ########.fr       */
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

			typedef ft::tree<value_type, value_compare, Allocator>	Tree;
			typedef typename Tree::iterator							iterator;
			typedef typename Tree::const_iterator					const_iterator;
			typedef typename Tree::reverse_iterator					reverse_iterator;
			typedef typename Tree::const_reverse_iterator			const_reverse_iterator;

			/* CONSTRUCTORS */

			map() : _tree(value_compare(Compare()), Allocator()) {}
			// explicit	map(const Compare &comp, const Allocator &alloc = Allocator()) : _tree(value_compare(comp), alloc) {}

			// template<class InputIt>
			// map(InputIt first, InputIt last, const Compare& comp = Compare(), const Allocator &alloc = Allocator()) : _tree(InputIt first, InputIt last, value_compare(comp, alloc)) {}
			// map(const map &other) : _tree(other._tree) {}
			/* --------- */

			/* DESTRUCTOR */

			// ~map() {}
			/* --------- */

			/* ASSIGN OPERATOR */

			// map	&operator=(const map &other) {
			// 	if (this == &other)
			// 		return (*this);
			// }
			/* --------- */

			// allocator_type	get_allocator() const { return (_tree.get_allocator()); }

			/* ELEMENT ACCESS */

			// reference	operator[](const Key &key) {}
			/* --------- */

			/* ITERATORS */

			iterator				begin() { return (_tree.begin()); }
			const_iterator			begin() { return (_tree.begin()); }

			iterator				end() { return (_tree.end()); }
			const_iterator			end() { return (_tree.end()); }

			reverse_iterator		rbegin() { return (_tree.rbegin()); }
			const_reverse_iterator	rbegin() { return (_tree.rbegin()); }

			reverse_iterator		rend() { return (_tree.rend()); }
			const_reverse_iterator	rend() { return (_tree.rend()) }
			/* --------- */

			/* CAPACITY */

			bool	empty() const { return (_tree.empty()); }

			size_type	size() const { return (_tree.size()); }

			size_type	max_size() const { return (_tree.max_size()); }
			/* --------- */

			/* MODIFIERS */

			// void	clear() { _tree.clear(); } // TODO needs check on deleteNode

			ft::pair<bool, iterator>	insert(const value_type &value) { return (_tree.insert(value)); }
			/* --------- */

			/* LOOKUP */

			size_type	count(const Key &key) const { return (_tree.count(key)); };
			/* --------- */
			void	print() const { _tree.print(); }

		private:
			Tree	_tree;
	};
}

#endif
