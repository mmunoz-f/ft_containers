/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   red_black_tree.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmunoz-f <mmunoz-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/17 17:58:46 by mmunoz-f          #+#    #+#             */
/*   Updated: 2021/10/18 18:12:31 by mmunoz-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __RED_BLACK_TREE_H__
# define __RED_BLACK_TREE_H__

namespace ft {

	template<class T>
	class	tree_iterator {

	};

	template<class T, class Compare, class Allocator>
	class	tree {

		public:
			typedef T									value_type;

			typedef Allocator							allocator_type;
			typedef typename Allocator::reference		reference;
			typedef typename Allocator::const_reference	const_reference;
			typedef typename Allocator::pointer			pointer;
			typedef typename Allocator::const_pointer	const_pointer;

			typedef struct node {
				bool		color;
				reference	content;
				struct node	*left;
				struct node	*right;
			} node;

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

		private:
			Compare			_comp;
			allocator_type	_alloc;
			node			*_root;
	};
}


#endif
