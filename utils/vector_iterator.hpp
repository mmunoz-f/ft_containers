#ifndef __VECTOR_ITERATOR_H__
# define __VECTOR_ITERATOR_H__

# include "utils.hpp"

namespace ft {
    /* vector RandomAccessIterator */

	template<class T>
	class vector_iterator {

		protected:
			T	_current;

		public:
			typedef typename ft::iterator_traits<T>::iterator_category	iterator_category;
			typedef typename ft::iterator_traits<T>::value_type			value_type;
			typedef typename ft::iterator_traits<T>::difference_type	difference_type;
			typedef typename ft::iterator_traits<T>::pointer			pointer;
			typedef typename ft::iterator_traits<T>::reference			reference;

			/* CONSTRUCTORS */

			vector_iterator() : _current() {}
			explicit	vector_iterator(T x) : _current(x) {}
			template<class U>
			vector_iterator(const vector_iterator<U> &other) : _current(other.base()) {}
			/* --------- */

			/* ASSIGN OPERATOR */

			template<class U>
			vector_iterator	&operator=(const vector_iterator<U> &other) {
				_current = other.base();
				return (*this);
			}
			/* --------- */

			T	base() const { return (_current); }

			/* ACCESS OPERATORS */

			reference	operator*() const { return *(_current); }
			pointer		operator->() const { return &(*_current); }

			reference	operator[](difference_type n) const { return *(_current + n); }
			/* --------- */

			/* ADVANCES AND DECREMENTS OPERATORS */

			vector_iterator	&operator++() {
				++_current;
				return (*this);
			}
			vector_iterator	&operator--() {
				--_current;
				return (*this);
			}

			vector_iterator	operator++(int) {
				vector_iterator	tmp(*this);
				++_current;
				return (tmp);
			}
			vector_iterator	operator--(int) {
				vector_iterator	tmp(*this);
				--_current;
				return (tmp);
			}

			vector_iterator	operator+(difference_type n) const { return (vector_iterator(base() + n)); }
			vector_iterator	operator-(difference_type n) const { return (vector_iterator(base() - n)); }

			template<class U>
			vector_iterator	&operator+=(U n) { return (*this = *this + n); }
			template<class U>
			vector_iterator	&operator-=(U n) { return (*this = *this - n); }
			/* --------- */
	};

	/* COMPARE OPERATORS */

	template<class T, class U>
	bool	operator==(const vector_iterator<T> &Iter1, const vector_iterator<U> &Iter2) { return (Iter1.base() == Iter2.base()); }
	template<class T, class U>
	bool	operator!=(const vector_iterator<T> &Iter1, const vector_iterator<U> &Iter2) { return !(Iter1 == Iter2); }
	template<class T, class U>
	bool	operator<(const vector_iterator<T> &Iter1, const vector_iterator<U> &Iter2) { return (Iter1.base() < Iter2.base()); }
	template<class T, class U>
	bool	operator<=(const vector_iterator<T> &Iter1, const vector_iterator<U> &Iter2) { return !(Iter2 < Iter1); }
	template<class T, class U>
	bool	operator>(const vector_iterator<T> &Iter1, const vector_iterator<U> &Iter2) { return (Iter2 < Iter1); }
	template<class T, class U>
	bool	operator>=(const vector_iterator<T> &Iter1, const vector_iterator<U> &Iter2) { return !(Iter1 < Iter2); }
	/* --------- */

	template<class T>
	vector_iterator<T>	operator+(typename vector_iterator<T>::difference_type n, const vector_iterator<T> &Iter) { return (Iter + n); }
	template<class T, class U>
	typename vector_iterator<T>::difference_type	operator-(const vector_iterator<T> &Iter1, const vector_iterator<U> &Iter2) { return (Iter1.base() - Iter2.base()); }

}

#endif