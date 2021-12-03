#ifndef __TREE_ITERATOR_H__
# define __TREE_ITERATOR_H__

# include "utils.hpp"

namespace   ft {
    
    template<class Node, class T>
	class	tree_iterator {
		public:
			typedef typename std::bidirectional_iterator_tag			iterator_category;
			typedef typename ft::iterator_traits<Node>::value_type		node;
			typedef typename ft::iterator_traits<Node>::difference_type	difference_type;
			typedef typename ft::iterator_traits<Node>::pointer			nodePtr;
			typedef typename ft::iterator_traits<Node>::reference		nodeRef;

			typedef T			value_type;
			typedef T&			reference;
			typedef T*			pointer;

			/* CONSTRUCTOR */

			tree_iterator() : _nill(), _current() {}
			tree_iterator(nodePtr x, nodePtr nill) : _nill(nill), _current(x) {}
			template<class N, class U>
			tree_iterator(const tree_iterator<N, U> &other) : _nill(other._nill), _current(other._current) {}
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

			nodePtr	base() const {return (_current); };

		template<class, class> friend class tree_iterator;
		template<class, class, class> friend class tree;
		template<class, class, class, class> friend class map;
		template<class, class, class> friend class set;

		template<class N1, class U, class N2, class V>
		friend bool	operator==(const tree_iterator<N1, U> &Iter1, const tree_iterator<N2, V> &Iter2);
		template<class N1, class U, class N2, class V>
		friend bool	operator<(const tree_iterator<N1, U> &Iter1, const tree_iterator<N2, V> &Iter2);
	};

	template<class N1, class T, class N2, class U>
	bool	operator==(const tree_iterator<N1, T> &Iter1, const tree_iterator<N2, U> &Iter2) { return (Iter1._current == Iter2._current); }
	template<class N1, class T, class N2, class U>
	bool	operator!=(const tree_iterator<N1, T> &Iter1, const tree_iterator<N2, U> &Iter2) { return !(Iter1 == Iter2); }
	template<class N1, class T, class N2, class U>
	bool	operator<(const tree_iterator<N1, T> &Iter1, const tree_iterator<N2, U> &Iter2) { return (Iter1._current > Iter2._current); }
	template<class N1, class T, class N2, class U>
	bool	operator<=(const tree_iterator<N1, T> &Iter1, const tree_iterator<N2, U> &Iter2) { return !(Iter2 < Iter1); }
	template<class N1, class T, class N2, class U>
	bool	operator>(const tree_iterator<N1, T> &Iter1, const tree_iterator<N2, U> &Iter2) { return (Iter2 < Iter1); }
	template<class N1, class T, class N2, class U>
	bool	operator>=(const tree_iterator<N1, T> &Iter1, const tree_iterator<N2, U> &Iter2) { return !(Iter1 < Iter2); }
}

#endif