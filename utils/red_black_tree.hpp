/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   red_black_tree.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmunoz-f <mmunoz-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/17 17:58:46 by mmunoz-f          #+#    #+#             */
/*   Updated: 2021/12/01 00:24:37 by mmunoz-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __RED_BLACK_TREE_H__
# define __RED_BLACK_TREE_H__

# include <memory>
# include "utils.hpp"
# include "node.hpp"
# include "tree_iterator.hpp"
# include "reverse_iterator.hpp"

# define M_BLACK	0
# define M_RED		1

namespace ft {
	
	template<class T, class Compare, class Allocator>
	class	tree {
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
		typedef ft::reverse_iterator<const_iterator>				const_reverse_iterator;

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
			n->right->color = M_BLACK;
			n->left->color = M_BLACK;
			n->color = M_RED;
		}

		void	leftCase(NodePtr &n) {
			if (n->getGrandParent()->right->color == M_RED) {
				reColorInsert(n->getGrandParent());
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

		void	rightCase(NodePtr &n) {
			if (n->getGrandParent()->left->color == M_RED) {
				reColorInsert(n->getGrandParent());
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
				if (newNode->getGrandParent()->left == newNode->parent)     
					leftCase(newNode);
				else
					rightCase(newNode);
				if (newNode == _root)
					break;
			}
		}

		bool	deleteCase0(NodePtr &x) {
			x->color = M_BLACK;
			return (false);
		}

		bool	deleteCase1(NodePtr &x, NodePtr &w) {
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

		bool	deleteCase2(NodePtr &x, NodePtr &w) {
			w->color = M_RED;
			x = x->parent;
			if (x->color == M_RED) {
				x->color = M_BLACK;
				return (false);
			}
			w = x->getSibling();
			return (true);
		}

		bool	deleteCase3(NodePtr &x, NodePtr &w) {
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

		bool	deleteCase4(NodePtr &x, NodePtr &w) {
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

		bool	fixDelete(NodePtr &x, NodePtr &w) {
			if (x->color == M_RED)
				return (deleteCase0(x));
			if (x->color == M_BLACK && w->color == M_RED)
				deleteCase1(x, w);
			if (x->color == M_BLACK && w->color == M_BLACK && w->right->color == M_BLACK && w->left->color == M_BLACK)
				return (deleteCase2(x, w));
			if (x->color == M_BLACK && w->color == M_BLACK && ((x->parent->left == x && w->left->color == M_RED && w->right->color == M_BLACK)
					|| (x->parent->right == x && w->right->color == M_RED && w->left->color == M_BLACK))) {
				deleteCase3(x, w);
				return (deleteCase4(x, w));
			}
			if (x->color == M_BLACK && w->color == M_BLACK && ((x->parent->left == x && w->right->color == M_RED) || (x->parent->right == x && w->left->color == M_RED)))
				return (deleteCase4(x, w));			
			return (true);
		}

		void	resetCore() {
			_nill->color = M_BLACK;
			_nill->parent = _nill;
			_nill->right = _root;
			_nill->left = _root;
			_root->parent = _nill;
			_root->color = M_BLACK;
		}

		/* CONSTRUCTORS */
		tree(const Compare &comp, const Allocator &alloc) : _comp(comp), _alloc(alloc), _nill(_alloc.allocate(1)), _root(_nill), _size(0) {
			_nill->color = M_BLACK;
			_nill->parent = _nill;
			_nill->left = _root;
			_nill->right = _root;
		}
		/* --------- */

		/* DESTRUCTOR */

		~tree() {
			_alloc.destroy(_nill);
			// _alloc.deallocate(_nill, 1);
		}
		/* --------- */

		Tree_allocator	get_Tree_allocator() const { return (_alloc); }
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

		reverse_iterator	rbegin() { return (reverse_iterator(end())); }
		const_reverse_iterator	rbegin() const { return (const_reverse_iterator(end())); }

		reverse_iterator	rend() { return (reverse_iterator(begin())); }
		const_reverse_iterator	rend() const { return (const_reverse_iterator(begin())); }
		/* --------- */

		/* CAPACITY */

		bool	empty() const { return (_root == _nill); }

		size_type	size() const { return (_size); }

		size_type	max_size() const { return (_alloc.max_size()); }
		/* --------- */

		/* INSERT */

		ft::pair<iterator, bool>	insertNode(const value_type &content) {
			NodePtr	newNode;
			if (empty()) {
				newNode = _alloc.allocate(1);
				_alloc.construct(newNode, Node(content, _nill));
				_root = newNode;
			}
			else {
				NodePtr i = _root;
				NodePtr p;
				while (i != _nill) {
					p = i;
					if (_comp(i->content, content))
						i = i->right;
					else if (_comp(content, i->content))
						i = i->left;
					else
						return (ft::pair<iterator, bool>(iterator(i, _nill), false));
				}
				newNode = _alloc.allocate(1);
				_alloc.construct(newNode, Node(content, _nill));
				NodePtr x = newNode;
				x->parent = p;
				_comp(p->content, content) ? p->right = x : p->left = x;
				fixInsert(x);
			}
			resetCore();
			_size++;
			return (ft::pair<iterator, bool>(iterator(newNode, _nill), true));
		}
		/* --------- */

		/* DELETE */

		void	deleteNode(NodePtr n) {
			NodePtr	x;
			NodePtr	y;
			NodePtr	w;
			if (n->left == _nill || n->right == _nill) {
				x = (n->left == _nill ? n->right : n->left);
				if (x != _nill)
					x->parent = n->parent;
				y = x;
				w = _nill;
			}
			else {
				x = n->getSuccesor(_nill);
				y = x->right;
				w = x->left;
				if (y != _nill)
					y->parent = x->parent;
				if (x == x->parent->left) {
					x->parent->left = y;
					w = x->parent->right;
				}
				else {
					x->parent->right = y;
					w = x->parent->left;
				}
				x->parent = n->parent;
				x->left = n->left;
				x->left->parent = x;
				x->right = n->right;
				x->right->parent = x;
			}
			n == n->parent->left ? n->parent->left = x : n->parent->right = x;
			if (n->color == M_RED && (x == _nill || x->color == M_RED));
			else if (n->color == M_RED && x->color == M_BLACK) {
				x->color = M_RED;
				while (fixDelete(y, w));
			}
			else if (n->color == M_BLACK && x->color == M_RED)
				x->color = M_BLACK;
			else if (n->color == M_BLACK && (x == _nill || x->color == M_BLACK))
				while (fixDelete(y, w));
			if (n == _root)
				_root = x;
			_alloc.destroy(n);
			_alloc.deallocate(n, 1);
			resetCore();
			_size--;
		}
		/* --------- */

		/* LOOKUP */

		size_type	count(const value_type &value) const {
			NodePtr		i = _root;
			while (i != _nill) {
				if (_comp(value, i->content))
					i = i->left;
				else if (_comp(i->content, value))
					i = i->right;
				else
					return (1);
			}
			return (0);
		}

		iterator	find(const value_type &value) {
			NodePtr	i = _root;
			while (i != _nill) {
				if (_comp(value, i->content))
					i = i->left;
				else if (_comp(i->content, value))
					i = i->right;
				else
					return (iterator(i, _nill));
			}
			return (end());
		}
		const_iterator	find(const value_type &value) const {
			NodePtr	i = _root;
			while (i != _nill) {
				if (_comp(value, i->content))
					i = i->left;
				else if (_comp(i->content, value))
					i = i->right;
				else
					return (const_iterator(i, _nill));
			}
			return (end());
		}

		void	swap(tree &other) {
			ft::swap(_nill, other._nill);
			ft::swap(_root, other._root);
			ft::swap(_size, other._size);
		}

		iterator		lower_bound(const value_type &value) {
			iterator	it(_root, _nill);
			while (it != end()) {
				if (_comp(*it, value))
					it++;
				else {
					iterator	aux(it);
					if (--aux == end() || _comp(*(aux++), value))
						return (it);
					it--;
				}
			}
			return (it);
		}
		const_iterator	lower_bound(const value_type &value) const {
			const_iterator	it(_root, _nill);
			while (it != end()) {
				if (_comp(*it, value))
					it++;
				else {
					const_iterator	aux(it);
					if (--aux == end() || _comp(*(aux++), value))
						return (it);
					it--;
				}
			}
			return (it);
		}

		iterator		upper_bound(const value_type &value) {
			iterator	it(_root, _nill);
			while (it != end()) {
				if (!_comp(value, *it))
					it++;
				else {
					iterator	aux(it);
					if (--aux == end() || !_comp(value, *(aux++)))
						return (it);
					it--;
				}
			}
			return (it);
		}
		const_iterator	upper_bound(const value_type &value) const {
			const_iterator	it(_root, _nill);
			while (it != end()) {
				if (!_comp(value, *it))
					it++;
				else {
					const_iterator	aux(it);
					if (--aux == end() || !_comp(value, *(aux++)))
						return (it);
					it--;
				}
			}
			return (it);
		}

		void print(const std::string& prefix = std::string(), const_NodePtr n = NULL, bool isLeft = false) const {
			if (n == NULL)
				n = _root;
			if (n != _nill) {
				std::cout << BKCOL << prefix << NOCOL;
				std::cout << BKCOL << (isLeft ? "├──" : "└──" ) << NOCOL;
				if (n->color == M_RED)
					std::cout << RDCOL << n->content.first << NOCOL << std::endl;
				else
					std::cout << n->content.first << NOCOL << std::endl;
				print(prefix + (isLeft ? "│   " : "    "), n->right, true);
				print(prefix + (isLeft ? "│   " : "    "), n->left, false);
			}
			else
				std::cout << BKCOL << prefix << NOCOL << "nill" << std::endl; 
		}

		Compare			_comp;
		Tree_allocator	_alloc;
		NodePtr			_nill;
		NodePtr			_root;

		size_type		_size;

		template<class, class, class, class> friend class map;
		template<class, class, class> friend class set;
		template<class U, class Comp, class Alloc>	
		friend void	swap(ft::tree<U, Comp, Alloc> lhs, ft::tree<U, Comp, Alloc> rhs);
	};

	template<class T, class Compare, class Allocator>
	void	swap(ft::tree<T, Compare, Allocator> &lhs, ft::tree<T, Compare, Allocator> &rhs) {
		lhs.swap(rhs);
	}
}

#endif
 