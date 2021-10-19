/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   red_black_tree.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmunoz-f <mmunoz-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/17 17:58:46 by mmunoz-f          #+#    #+#             */
/*   Updated: 2021/10/19 23:00:16 by mmunoz-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __RED_BLACK_TREE_H__
# define __RED_BLACK_TREE_H__

# include "utils.hpp"

# define M_BLACK	0
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

			tree_iterator() : _nill(), _root(), _current() {}
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

	template<class T, class Compare>
	class	tree {

		typedef struct node {
			bool	color;
			T		*content;
			node	*parent;
			node	*left;
			node	*right;

			node(const value_type *value = NULL, const bool color = M_BLACK) : color(color), content(value), parent(), left(), right() {}

			node	&operator=(const node &other) {
				if (this == &other)
					return (*this);
				color = other.color;
				content = other.content;
				parent = other.parent;
				left = other.left;
				right = other.right;
			}

			reference	operator*() { return (*content); }
			pointer		operator->() { return (content); }
		} node;

		public:
			typedef T										value_type;

			typedef std::allocator<node>					Allocator;
			typedef typename Allocator::reference			reference;
			typedef typename Allocator::const_reference		const_reference;
			typedef typename Allocator::pointer				pointer;
			typedef typename Allocator::const_pointer		const_pointer;

			/* CONSTRUCTORS */

			tree(const Compare &comp, const Allocator &alloc) : _comp(comp), _alloc(alloc), _nill(_alloc.allocate(1)), _root(_nill) {}
			template<class InputIt>
			tree(InputIt first, InputIt last, const Compare &comp, const Allocator &alloc) : _comp(comp), _alloc(alloc), _nill(_alloc.allocate(1)), _root(_nill) {}
			tree(const tree &other) : _comp(other._comp), _alloc(other._alloc), _nill(_alloc.allocate(1)), _root(_nill) {

			}
			/* --------- */

			/* DESTRUCTOR */

			~tree() {}
			/* --------- */

			/* ASSIGN OPERATOR */

			tree	&operator=(const tree &other) {
				if (this == &other)
					return (*this);
				_alloc = other._alloc;
				_root = NULL;
				_nill = _alloc.allocate(1);
			}
			/* --------- */

			allocator_type	get_allocator() const { return (_alloc); }

			/* INSERT */

			void	insert(const value_type &content) {
				bool		way;
				node		*current = _root;
				node		*new_node = _alloc.allocate(1);
				*new_node	= node(&content, M_RED);

				for (node *next = current; next != _nill;) {
					current = next;
					(way = _comp(*(*current), *(*new_node))) ? next = current->left : next = current->right;
				}
				if (current == _root) {
					_root = new_node;
					new_node->color = M_BLACK;
				}
				else
					way ? current->left = new_node : current->right = new_node;
				new_node->left = _nill;
				new_node->right = _nill;
			}
			/* --------- */
		private:
			Compare			_comp;
			Allocator		_alloc;
			node			*_nill;
			node			*_root;
	};
}


#endif
