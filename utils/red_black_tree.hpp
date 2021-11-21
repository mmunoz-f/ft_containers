/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   red_black_tree.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmunoz-f <mmunoz-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/17 17:58:46 by mmunoz-f          #+#    #+#             */
/*   Updated: 2021/11/21 20:00:57 by mmunoz-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __RED_BLACK_TREE_H__
# define __RED_BLACK_TREE_H__

# include <memory>
# include "utils.hpp"
# include "node.hpp"

# define M_BLACK	0
# define M_RED		1

namespace ft {

	template<class Node>
	class	tree_iterator {
		public:
			typedef typename std::bidirectional_iterator_tag			iterator_category;
			typedef typename ft::iterator_traits<Node>::value_type		node;
			typedef typename ft::iterator_traits<Node>::difference_type	difference_type;
			typedef typename ft::iterator_traits<Node>::pointer			nodePtr;
			typedef typename ft::iterator_traits<Node>::reference		nodeRef;

			typedef typename ft::node_traits<Node>::value_type			value_type;
			typedef typename ft::node_traits<Node>::reference			reference;
			typedef typename ft::node_traits<Node>::pointer				pointer;

			/* CONSTRUCTOR */

			tree_iterator() : _nill(), _current() {}
			tree_iterator(nodePtr x, nodePtr nill) : _nill(nill), _current(x) {}
			tree_iterator(const tree_iterator &other) : _nill(other._nill), _current(other._current) {}
			/* --------- */

			/* ASSIGN OPERATOR */

			tree_iterator	&operator=(const tree_iterator &other) {
				_nill = other._nill;
				_current = other._current;
				return (*this);
			}
			/* --------- */

			/* ACCESS OPERATOR */

			reference	operator*() const { return (_current->content); }
			pointer		operator->() const { return &(_current->content); }
			/* --------- */

			/* ADVANCES AND DECREMENTS OPERATORS */
			tree_iterator	&operator++() {
				if (_current->right != _nill) {
					_current = _current->right;
					while (_current->left != _nill)
						_current = _current->left;
				}
				else
					while (_current != _current->parent->left && _current != _nill)
						_current = _current->parent;
				return (*this);
			}
			tree_iterator	&operator--() {
				if (_current->left != _nill) {
					_current = _current->left;
					while (_current->right != _nill)
						_current = _current->right;
				}
				else
					while (_current != _current->parent->right && _current != _nill)
						_current = _current->left;
				return (*this);
			}

			tree_iterator	operator++(int) {
				tree_iterator	tmp(*this);
				++(*this);
				return (tmp);
			}
			tree_iterator	operator--(int) {
				tree_iterator	tmp(*this);
				--(*this);
				return (tmp);
			}
		private:
			nodePtr	_nill;
			nodePtr	_current;

		template<class T>
		friend bool	operator==(const tree_iterator<T> &Iter1, const tree_iterator<T> &Iter2);
		template<class T>
		friend bool	operator<(const tree_iterator<T> &Iter1, const tree_iterator<T> &Iter2);
	};

	template<class T>
	bool	operator==(const tree_iterator<T> &Iter1, const tree_iterator<T> &Iter2) { return (Iter1._current == Iter2._current); }
	template<class T>
	bool	operator!=(const tree_iterator<T> &Iter1, const tree_iterator<T> &Iter2) { return !(Iter1 == Iter2); }
	template<class T>
	bool	operator<(const tree_iterator<T> &Iter1, const tree_iterator<T> &Iter2) { return (Iter1._current > Iter2._current); }
	template<class T>
	bool	operator<=(const tree_iterator<T> &Iter1, const tree_iterator<T> &Iter2) { return !(Iter2 < Iter1); }
	template<class T>
	bool	operator>(const tree_iterator<T> &Iter1, const tree_iterator<T> &Iter2) { return (Iter2 < Iter1); }
	template<class T>
	bool	operator>=(const tree_iterator<T> &Iter1, const tree_iterator<T> &Iter2) { return !(Iter1 < Iter2); }

	template<class T, class Compare, class Allocator>
	class	tree {
		public:
			typedef T													value_type;

			typedef std::size_t											size_type;

			typedef node<T>												Node;
			typedef typename Allocator::template rebind<Node>::other	Tree_allocator;
			typedef typename Tree_allocator::reference					reference;
			typedef typename Tree_allocator::const_reference			const_reference;
			typedef typename Tree_allocator::pointer					NodePtr;
			typedef typename Tree_allocator::const_pointer				const_NodePtr;

			typedef ft::tree_iterator<NodePtr>							iterator;
			typedef ft::tree_iterator<const_NodePtr>					const_iterator;
			typedef ft::reverse_iterator<iterator>						reverse_iterator;
			typedef ft::reverse_iterator<const_NodePtr>					const_reverse_iterator;

		private:
			void	leftRotate(NodePtr x) {
				NodePtr y = x->right;
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

			void	rightRotate(NodePtr y) {
				NodePtr x = y->left;
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

			static void	reColorInsert(NodePtr n) {
				n->getGrandParent()->right->color = M_BLACK;
				n->getGrandParent()->left->color = M_BLACK;
				n->getGrandParent()->color = M_RED;
			}

			void	leftCase(NodePtr n) {
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

			void	rightCase(NodePtr n) {
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

			void	fixInsert(NodePtr newNode) {
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

			NodePtr	replaceNill(NodePtr n) {
				NodePtr x;
				x = (n->left == _nill ? n->right : n->left);
				if (n->parent->left == n)
					n->parent->left = x;
				else
					n->parent->right = x;
				return (x);
			}

			bool	deleteCase0(NodePtr x) {
				x->color = M_BLACK;
				return (false);
			}

			bool	deleteCase1(NodePtr x, NodePtr w) {
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

			bool	deleteCase2(NodePtr x, NodePtr w) {
				w->color = M_RED;
				x = x->parent;
				if (x->color == M_RED) {
					x->color = M_BLACK;
					return (false);
				}
				w = x->getSibling();
				return (true);
			}

			bool	deleteCase3(NodePtr x, NodePtr w) {
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

			bool	deleteCase4(NodePtr x, NodePtr w) {
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

			bool	reColorDelete(NodePtr x, NodePtr w) {
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
				_nill->right = _root;
				_nill->left = _root;
			}

		public:

			/* CONSTRUCTORS */

			tree(const Compare &comp, const Tree_allocator &alloc) : _comp(comp), _alloc(alloc), _nill(_alloc.allocate(1)), _root(_nill), _size(0) {
				_nill->color = M_BLACK;
				_nill->parent = _nill;
				_nill->left = _nill;
				_nill->right = _nill;
			}
			// template<class InputIt>
			// tree(InputIt first, InputIt last, const Compare &comp, const Tree_allocator &alloc) : _comp(comp), _alloc(alloc), _nill(_alloc.allocate(1)), _root(_nill), _size(0) {
			// 	for (; first != last; firsr++)
			// 		insert(*first);
			// }
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

			/* ACCESS OPERATOR */

			/* --------- */

			/* ITERATORS */

			iterator	begin() {
				NodePtr i = _root;
				while (i->left != _nill)
					i = i->left;
				return (iterator(i, _nill));
			}
			const_iterator	begin() const {
				NodePtr i = _root;
				while (i->left != _nill)
					i = i->left;
				return (const_iterator(i, _nill));
			}

			iterator	end() { return (iterator(_nill, _nill)); }
			const_iterator	end() const { return (const_iterator(_nill, _nill)); }

			reverse_iterator	rbegin() { return (reverse_iterator(begin())); }
			const_reverse_iterator	rbegin() const { return (const_reverse_iterator(begin())); }

			reverse_iterator	rend() { return (reverse_iterator(end())); }
			const_reverse_iterator	rend() const { return (const_reverse_iterator(end())); }
			/* --------- */

			/* CAPACITY */

			bool	empty() const { return (_root == _nill); }

			size_type	size() const { return (_size); }

			size_type	max_size() const { return (_alloc.max_size()); }
			/* --------- */

			/* INSERT */

			iterator	insertNode(const value_type &content) {
				NodePtr	newNode = _alloc.allocate(1);
				_alloc.construct(newNode, Node(content, _nill));
				NodePtr x = newNode;
				if (empty()) {
					x->color = M_BLACK;
					_root = x;
					return (iterator(newNode, _nill));
				}
				NodePtr i = _root;
				NodePtr p;
				while (i != _nill) {
					p = i;
					if (_comp(i->content, x->content))
						i = i->right;
					else
						i = i->left;
				}
				x->parent = p;
				x->color = M_RED;
				_comp(p->content, x->content) ? p->right = x : p->left = x;
				fixInsert(x);
				resetNill();
				_size++;
				return (iterator(newNode, _nill));
			}
			/* --------- */

			/* DELETE */

			// void	deleteNode(NodePtr n) {
			// 	bool	originalColor = n->color;
			// 	NodePtr	x;
			// 	if (n->left == _nill || n->right == _nill)
			// 		x = replaceNill(n);
			// 	else {
			// 		x = n->getSuccesor(_nill);
			// 		x->parent->left = _nill;
			// 	}
			// 	if (n->color == M_RED && (x == _nill || x->color == M_RED))
			// 		return ;
			// 	else if (n->color == M_RED && x->color == M_BLACK)
			// 		x->color = M_RED;
			// 	else if (x->color == M_RED) {
			// 		x->color = M_BLACK;
			// 		return ;
			// 	}
			// 	NodePtr w = x->getSibling();
			// 	while (reColorDelete(x, w));
			// 	resetNill();
			// 	_size()--;
			// }
			/* --------- */

			/* LOOKUP */

			/* --------- */
			void print(const std::string& prefix = std::string(), const_NodePtr n = NULL, bool isLeft = false) const {
				if (n == NULL)
					n = _root;
				if (n != _nill) {
					std::cout << BKCOL << prefix << NOCOL;
					std::cout << BKCOL << (isLeft ? "├──" : "└──" ) << NOCOL;
					if (n->color == M_RED)
						std::cout << RDCOL << n->content.first << NOCOL << std::endl;
					else {
						if (n->content.first == -1)
							std::cout << "nil" << NOCOL << std::endl;
						else
							std::cout << n->content.first << NOCOL << std::endl;
					}
					print(prefix + (isLeft ? "│   " : "    "), n->right, true);
					print(prefix + (isLeft ? "│   " : "    "), n->left, false);
				}
			}

		private:
			Compare			_comp;
			Tree_allocator	_alloc;
			NodePtr			_nill;
			NodePtr			_root;

			size_type		_size;
	};
}


#endif
