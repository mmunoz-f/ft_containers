#ifndef __TREE_ITERATOR_H__
# define __TREE_ITERATOR_H__

# include "utils.hpp"

namespace   ft {
    
    template<class Node>
	class	tree_iterator {
		public:
			typedef typename std::bidirectional_iterator_tag			iterator_category;
			typedef typename ft::iterator_traits<Node>::value_type		node;
			typedef typename ft::iterator_traits<Node>::difference_type	difference_type;
			typedef typename ft::iterator_traits<Node>::pointer			nodePtr;
			typedef typename ft::iterator_traits<Node>::reference		nodeRef;

			typedef typename ft::node_traits<nodePtr>::value_type		value_type;
			typedef typename ft::node_traits<nodePtr>::reference		reference;
			typedef typename ft::node_traits<nodePtr>::pointer			pointer;

			/* CONSTRUCTOR */

			tree_iterator() : _nill(), _current() {}
			tree_iterator(nodePtr x, nodePtr nill) : _nill(nill), _current(x) {}
			template<class U>
			tree_iterator(const tree_iterator<U> &other) : _nill(other._nill), _current(other._current) {}
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
				else {
					while (_current != _current->parent->left && _current->parent != _nill)
						_current = _current->parent;
					_current = _current->parent;
				}
				return (*this);
			}
			tree_iterator	&operator--() {
				if (_current->left != _nill) {
					_current = _current->left;
					while (_current->right != _nill)
						_current = _current->right;
				}
				else {
					while (_current != _current->parent->right && _current->parent != _nill)
						_current = _current->parent;
					_current = _current->parent;
				}
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

			nodePtr	base() {return (_current); };

		template<class> friend class tree_iterator;
		template<class, class, class> friend class tree;
		template<class, class, class, class> friend class map;
		template<class, class, class> friend class set;

		template<class T, class U>
		friend bool	operator==(const tree_iterator<T> &Iter1, const tree_iterator<U> &Iter2);
		template<class T, class U>
		friend bool	operator<(const tree_iterator<T> &Iter1, const tree_iterator<U> &Iter2);
	};

	template<class T, class U>
	bool	operator==(const tree_iterator<T> &Iter1, const tree_iterator<U> &Iter2) { return (Iter1._current == Iter2._current); }
	template<class T, class U>
	bool	operator!=(const tree_iterator<T> &Iter1, const tree_iterator<U> &Iter2) { return !(Iter1 == Iter2); }
	template<class T, class U>
	bool	operator<(const tree_iterator<T> &Iter1, const tree_iterator<U> &Iter2) { return (Iter1._current > Iter2._current); }
	template<class T, class U>
	bool	operator<=(const tree_iterator<T> &Iter1, const tree_iterator<U> &Iter2) { return !(Iter2 < Iter1); }
	template<class T, class U>
	bool	operator>(const tree_iterator<T> &Iter1, const tree_iterator<U> &Iter2) { return (Iter2 < Iter1); }
	template<class T, class U>
	bool	operator>=(const tree_iterator<T> &Iter1, const tree_iterator<U> &Iter2) { return !(Iter1 < Iter2); }
}

#endif