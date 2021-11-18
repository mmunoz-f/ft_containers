/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   red_black_tree.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmunoz-f <mmunoz-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/17 17:58:46 by mmunoz-f          #+#    #+#             */
/*   Updated: 2021/11/18 03:25:37 by mmunoz-f         ###   ########.fr       */
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

	template<class T>
	class	node {
		public:
			T		content;
			node	*parent;
			node	*left;
			node	*right;
			bool		color;

			node() : color(M_RED) {}
			node(const T value,  node *nill) : content(value), parent(nill), left(nill), right(nill) {}
			node(const  node &other) : content(other.content), parent(other.parent), left(other.left), right(other.right), color(other.color) {}

			node	*getGrandParent() {
				return (parent->parent);
			}

			node	*getSuccesor(node *nill) {
				node	*s = right;
				while (s->left != nill)
					s = s->left;
				return (s);
			}

			node	*getSibling() {
				if (this == parent->right)
					return (parent->left);
				return (parent->right);
			}

			T&		operator*() { return (content); }
			T*		operator->() { return (&content); }
	};

	template<class T, class Compare, class Allocator>
	class	tree {
		public:
			typedef T													value_type;

			typedef node<T>												node;
			typedef typename Allocator::template rebind<node>::other	Tree_allocator;
			typedef typename Tree_allocator::reference					reference;
			typedef typename Tree_allocator::const_reference			const_reference;
			typedef typename Tree_allocator::pointer					pointer;
			typedef typename Tree_allocator::const_pointer				const_pointer;

		private:
			void	leftRotate(node *x) {
				node	*y = x->right;
				x->right = y->left;
				if (y->left != _nill)
					y->left->parent = x;
				y->parent = x->parent;
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
				y->left = x->right;
				if (x->right != _nill)
					x->right->parent = y;
				x->parent = y->parent;
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

			static void	reColorInsert(node *n) {
				n->getGrandParent()->right->color = M_BLACK;
				n->getGrandParent()->left->color = M_BLACK;
				n->getGrandParent()->color = M_RED;
			}

			void	leftCase(node *n) {
				if (n->getGrandParent()->right->color == M_RED) {
					reColorInsert(n);
					n = n->getGrandParent();
				}
				else {
					if (n == n->parent->right) { // Case 2
						n = n->parent;
						leftRotate(n);
					}
					n->parent->color = M_BLACK;
					n->getGrandParent()->color = M_RED;
					rightRotate(n->getGrandParent());
				}
			}

			void	rightCase(node *n) {
				if (n->getGrandParent()->left->color == M_RED) {
					reColorInsert(n);
					n = n->getGrandParent();
				}
				else {
					if (n == n->parent->left) {
						n = n->parent;
						rightRotate(n);
					}
					n->parent->color = M_BLACK;
					n->getGrandParent()->color = M_RED;
					leftRotate(n->getGrandParent());
				}
			}

			void	fixInsert(node *newNode) {
				while (newNode->parent->color == M_RED) {
					if (newNode->getGrandParent()->left == newNode->parent) // Case 1
						leftCase(newNode);
					else {
						rightCase(newNode);
					}
					if (newNode == _root)
						break;
				}
				_root->color = M_BLACK;
			}

			node	*replaceNill(node *n) {
				node	*x;
				x = (n->left == _nill ? n->right : n->left);
				if (n->parent->left == n)
					n->parent->left = x;
				else
					n->parent->right = x;
				return (x);
			}

			static bool	deleteCase0(node &*x) {
				x->color = M_BLACK;
				return (false);
			}

			static bool	deleteCase1(node &*x, node &*w) {
				w->color = M_BLACK;
				x->parent->color = M_RED;
				if (x == x->parent->left)
					leftRotate(x->parent);
				else
					rightRotate(x->parent);
				if (x == x->parent->left)
					w = x->parent->right;
				else
					w = x->parent->left;
				return (true);
			}

			static bool	deleteCase2(node &*x, node &*w) {
				w->color = M_RED;
				x = x->parent;
				if (x->color == M_RED) {
					x->color = M_BLACK;
					return (false);
				}
				w = x->getSibling();
				return (true);
			}

			static bool	deleteCase3(node &*x, node &*w) {
				if (x == x->parent->left) {
					w->left->color = M_BLACK;
					w->color = M_RED;
					rightRotate(w);
					w = x->parent->right;
				}
				else {
					w->right->color = M_BLACK;
					w->color = M_RED;
					leftRotate(w);
					w = x->parent->left;
				}
				return (deleteCase4(x, w));
			}

			static bool	deleteCase4(node &*x, node &*w) {
				w->color = x->parent->color;
				x->parent->color = M_BLACK;
				if (x == x->parent->left) {
					w->right->color = M_BLACK;
					leftRotate(x->parent);
				}
				else {
					w->left->color = M_BLACK;
					rightRotate(x->parent);
				}
				return (false);
			}

			static bool	reColorDelete(node &*x, node &*w) {
				if (x->color == M_RED)
					return (deleteCase0(x));
				else if (w->color == M_RED)
					return (deleteCase1(x, w));
				else if (w->right->color == M_BLACK && w->left->color == M_BLACK)
					return (deleteCase2(x, w));
				else if ((x->parent->left == x && w->left->color == M_RED && w->right->color == M_BLACK)
						|| (x->parent->right == x && w->right->color == M_RED && w->left->color == M_BLACK))
					return (deleteCase3(x, w));
				else if ((x->parent->left == x && w->right->color == M_RED) || (x->parent->right == x && w->left->color == M_RED))
					return (deleteCase4(x, w));
				return (true);
			}

			void	resetNill() {
				_nill->color = M_BLACK;
				_nill->parent = _nill;
				_nill->right = _nill;
				_nill->left = _nill;
			}

		public:

			/* CONSTRUCTORS */

			tree(const Compare &comp, const Tree_allocator &alloc) : _comp(comp), _alloc(alloc), _nill(_alloc.allocate(1)), _root(_nill) {
				_nill->color = M_BLACK;
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
				_alloc.construct(newNode, node(content, _nill));
				if (empty()) {
					newNode->color = M_BLACK;
					_root = newNode;
					return ;
				}
				node	*i = _root;
				node	*p;
				while (i != _nill) {
					p = i;
					if (_comp(*(*i), *(*newNode)))
						i = i->right;
					else
						i = i->left;
				}
				newNode->parent = p;
				newNode->color = M_RED;
				_comp(*(*p), *(*newNode)) ? p->right = newNode : p->left = newNode;
				fixInsert(newNode);
			}
			/* --------- */

			/* DELETE */

			void	deleteNode(node	*n) {
				bool	originalColor = n->color;
				node	*x;
				if (n->left == _nill || n->right == _nill)
					x = replaceNill(node);
				else {
					x = n->getSuccesor(_nill);
					x->parent->left = _nill;
				}
				if (n->color == M_RED && (x == _nill || x->color == M_RED))
					return ;
				else if (n->color == M_RED && x->color == M_BLACK)
					x->color = M_RED;
				else if (x->color == M_RED) {
					x->color = M_BLACK;
					return ;
				}
				node	*w = x->getSibling();
				while (reColorDelete(x, w));
				resetNill();
			}
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
