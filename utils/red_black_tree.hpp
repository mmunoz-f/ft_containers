/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   red_black_tree.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmunoz-f <mmunoz-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/17 17:58:46 by mmunoz-f          #+#    #+#             */
/*   Updated: 2021/11/15 21:11:07 by mmunoz-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __RED_BLACK_TREE_H__
# define __RED_BLACK_TREE_H__

# include <memory>
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

			/* ACCESS OPERATOR */

			reference	operator*() const { return (*_current); }
			pointer		operator->() const { return &(*_current); }
			/* --------- */
	};

	template<class T, class Compare, class Allocator>
	class	tree {

		typedef struct	node {
			T			content;
			node		*parent;
			node		*left;
			node		*right;
			bool		color;

			node(const T value, const node *nill) : content(value), parent(nill), left(nill), right(nill) {}

			node	&operator=(const node &other) {
				if (this == &other)
					return (*this);
				color = other.color;
				content = other.content;
				parent = other.parent;
				left = other.left;
				right = other.right;
			}

			node	*getGrandParent() {
				return (parent->parent);
			}

			T&		operator*() { return (*content); }
			T*		operator->() { return (content); }
		}	node;

		public:
			typedef T															value_type;

			typedef typename Allocator::template	rebind<struct node>::other	Tree_allocator;
			typedef typename Tree_allocator::reference							reference;
			typedef typename Tree_allocator::const_reference					const_reference;
			typedef typename Tree_allocator::pointer							pointer;
			typedef typename Tree_allocator::const_pointer						const_pointer;

		private:
			void	leftRotate(node *x) {
				node	*y = x->right;
				if (y->left != _nill) {
					y->left->parent = x;
					x->right = y->left;
				}
				if (x->parent == _nill)
					_root = y;
				else if (x == x->parent->left)
					x->parent->left = y;
				else
					x->parent->right = y;
				x->parent = y;
				y->left = x;
			}

			void	rightRotate(node *y) {
				node	*x = y->left;
				if (x->right != _nill) {
					x->right->parent = y;
					y->left = x->right;
				}
				if (y->parent == _nill)
					_root = x;
				else if (y == y->parent->right)
					y->parent->right = x;
				else
					y->parent->left = x;
				y->parent = x;
				x->right = y;
			}

			void	leftRightRotate(node *z) {
				node	*x = z->left;
				leftRotate(x);
				rightRotate(z);
			}

			void	rightLeftRotate(node *z) {
				node	*x = z->right;
				rightRotate(x);
				leftRotate(z);
			}

			void	fixInsert(node *newNode) {
				while (newNode->parent->color == M_RED) {
					if (newNode->getGrandParent()->left == newNode->parent) { // Case 1
						if (newNode->getGrandParent()->right->color == M_RED) {
							newNode->getGrandParent()->right = M_BLACK;
							newNode->getGrandParent()->left = M_BLACK;
							newNode->getGrandParent()->color = M_RED;
							newNode = newNode->getGrandParent();
						}
						else if (newNode == newNode->parent->right) { // Case 2
							newNode = newNode->parent;
							leftRotate(newNode);
						}
						else { // Case 3
							newNode->parent->color = M_BLACK;
							newNode->getGrandParent()->colot = M_RED;
							rightRoatate(newNode->getGrandParent());
						}
					}
					else {
						if (newNode->getGrandParent()->left->color == M_RED) {
							newNode->getGrandParent()->left->color = M_BLACK;
							newNode->getGrandParent()->right->color = M_BLACK;
							newNode->getGrandParent()->color = M_RED;
							newNode = newNode->getGrandParent();
						}
						else {
							if (newNode == newNode->parent->left) {
								newNode = newNode->parent;
								rightRotate(newNode);
							}
							newNode->parent->color = M_BLACK;
							newNode->getGrandParent()->color = M_RED;
							leftRotate(newNode->getGrandParent());
						}
					}
				}
				_root->color = M_BLACK;
			}

		public:

			/* CONSTRUCTORS */

			tree(const Compare &comp, const Tree_allocator &alloc) : _comp(comp), _alloc(alloc), _nill(_alloc.allocate(1)), _root(_nill) {
				_nill->parent = _nill;
				_nill->left = _nill;
				_nill->right = _nill;
			}
			// template<class InputIt>
			// tree(InputIt first, InputIt last, const Compare &comp, const Tree_allocator &alloc) : _comp(comp), _alloc(alloc), _nill(_alloc.allocate(1)), _root(_nill) {}
			// tree(const tree &other) : _comp(other._comp), _alloc(other._alloc), _nill(_alloc.allocate(1)), _root(_nill) {

			// }
			/* --------- */

			/* DESTRUCTOR */

			~tree() {}
			/* --------- */

			/* ASSIGN OPERATOR */

			// tree	&operator=(const tree &other) {
			// 	if (this == &other)
			// 		return (*this);
			// 	_alloc = other._alloc;
			// 	_root = NULL;
			// 	_nill = _alloc.allocate(1);
			// }
			/* --------- */

			Tree_allocator	get_Tree_allocator() const { return (_alloc); }

			/* CAPACITY */

			bool	empty() const { return (_root == _nill); }
			/* --------- */

			/* INSERT */

			void	insert(const value_type &content) {
				node	*newNode = _alloc.allocate(1);
				*newNode = node(content, _nill);
				if (empty()) {
					newNode->color = M_BLACK;
					return (_root = newNode);
				}
				node	*i = _root;
				for (; i != _nill;) {
					if (_comp(*i, newNode))
						i = i->right;
					else
						i = i->left;
				}
				newNode->parent = i->parent;
				newNode->color = M_RED;
				_comp(*(i->parent), newNode) ? *(i->parent.right) = newNode : *(i->parent.left) = newNode;
				fixInsert(newNode);
			}
			/* --------- */

			/* DELETE */

			// void	deleteNode(node	*node) {
			// 	bool	originalColor = node->color;
			// }
			/* --------- */

			void print(const std::string& prefix = std::string(), const node* node = NULL, bool isLeft = false) const {
				if (node == NULL)
					node = _root;
				if (node != _nill) {
					std::cout << BKCOL << prefix << NOCOL;
					std::cout << BKCOL << (isLeft ? "├──" : "└──" ) << NOCOL;
					if (node->color == M_RED)
						std::cout << RDCOL << node->content.first << NOCOL << std::endl;
					else {
						if (node->content.first == -1)
							std::cout << "nil" << NOCOL << std::endl;
						else
							std::cout << node->content.first << NOCOL << std::endl;
					}
					print(prefix + (isLeft ? "│   " : "    "), node->right, true);
					print(prefix + (isLeft ? "│   " : "    "), node->left, false);
				}
			}

		private:
			Compare			_comp;
			Tree_allocator	_alloc;
			node			*_nill;
			node			*_root;
	};
}


#endif
