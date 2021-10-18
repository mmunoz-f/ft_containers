/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   red_black_tree.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miguel <miguel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/17 17:58:46 by mmunoz-f          #+#    #+#             */
/*   Updated: 2021/10/18 21:03:06 by miguel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __RED_BLACK_TREE_H__
# define __RED_BLACK_TREE_H__

# include "utils.hpp"

# define M_NEGRO	0
# define M_RED		1

namespace ft {

	template<class T>
	class	tree_iterator {

		protected:
			T	_nill;
			T	_root;
			T	_current;

		public:
			typedef typename std::bidirectional_iterator_tag			iterator_category;
			typedef typename ft::iterator_traits<T>::value_type			value_type;
			typedef typename ft::iterator_traits<T>::difference_type	difference_type;
			typedef typename ft::iterator_traits<T>::pointer			pointer;
			typedef typename ft::iterator_traits<T>::reference			reference;

			/* CONSTRUCTOR */

			tree_iterator() : _current() {}
			explicit	tree_iterator(T x) : _current(x) {}
			template<class U>
			tree_iterator(const tree_iterator<U> &other) : _current(other.base()) {}
			/* --------- */

			/* ASSIGN OPERATOR */

			template<class U>
			tree_iterator	&operator=(const tree_iterator<U> &other) {
				_current = other.base();
				return (*this);
			}
			/* --------- */

			T base() const { return (_current); }

			/* ACCES OPERATOR */

			reference	operator*() const { return *(_current); }
			pointer		operator->() const { return &(*_current); }
			/* --------- */
	};

	template<class T, class Compare, class Allocator>
	class	tree {

		struct node;

		public:
			typedef T										value_type;

			typedef Allocator								allocator_type;
			typedef typename Allocator::reference			reference;
			typedef typename Allocator::const_reference		const_reference;
			typedef typename Allocator::pointer				pointer;
			typedef typename Allocator::const_pointer		const_pointer;


			typedef tree_iterator<node>						iterator;
			typedef tree_iterator<const node>				const_iterator;
			typedef ft::reverse_iterator<iterator>			reverse_iterator;
			typedef ft::reverse_iterator<const_iterator>	const_reverse_iterator;

			/* CONSTRUCTORS */

			tree(const Compare &comp, const Allocator &alloc) : _comp(comp), _alloc(alloc), _root(NULL) {}
			template<class InputIt>
			tree(InputIt first, InputIt last, const Compare &comp, const Allocator &alloc) : _comp(comp), _alloc(alloc),  _root(NULL) {}
			tree(const tree &other) {

			}
			/* --------- */

			/* DESTRUCTOR */

			~tree() {}
			/* --------- */

			/* ASSIGN OPERATOR */

			tree	&operator=(const tree &other) {
				if (this == &other)
					return (*this);
			}
			/* --------- */

			allocator_type	get_allocator() const { return (_alloc); }

			/* ACCESS OPERATOR */


			/* --------- */

			/* ITERATORS */


			/* --------- */

		private:
			Compare			_comp;
			allocator_type	_alloc;
			node			*_root;
			node			*_nill;

			typedef struct node {
				bool		color;
				reference	content;
				node		*parent;
				node		*left;
				node		*right;

				node(const value_type &value, const bool color = M_RED) : color(color), content(value) {}

				reference	operator*() { return (content); }
			} node;
	};
}


#endif
