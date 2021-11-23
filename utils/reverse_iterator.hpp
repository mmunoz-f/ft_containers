/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reverse_iterator.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmunoz-f <mmunoz-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/02 03:30:55 by mmunoz-f          #+#    #+#             */
/*   Updated: 2021/11/21 16:35:42 by mmunoz-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __REVERSE_ITERATOR_H__
# define __REVERSE_ITERATOR_H__

# include "utils.hpp"

namespace ft {

	/* Reverse iterator reimplementation */

	template<class T>
	class	reverse_iterator {

		protected:
			T	_current;

		public:
			typedef typename ft::iterator_traits<T>::iterator_category	iterator_category;
			typedef typename ft::iterator_traits<T>::value_type			value_type;
			typedef typename ft::iterator_traits<T>::difference_type	difference_type;
			typedef typename ft::iterator_traits<T>::pointer			pointer;
			typedef typename ft::iterator_traits<T>::reference			reference;

			/* CONSTRUCTORS */

			reverse_iterator() : _current() {}
			explicit	reverse_iterator(T x) : _current(x) {}
			template<class U>
			reverse_iterator(const reverse_iterator<U> &other) : _current(other.base()) {}
			/* --------- */

			/* ASSIGN OPERATOR */

			template<class U>
			reverse_iterator	&operator=(const reverse_iterator<U> &other) {
				_current = other.base();
				return (*this);
			}
			/* --------- */

			T	base() const { return (_current); }

			/* ACCESS OPERATORS */

			reference	operator*() const { return *(--(T(_current))); }
			pointer		operator->() const { return &(*(*this)); }

			reference	operator[](difference_type n) const { return *(*this + n); }
			/* --------- */

			/* ADVANCES AND DECREMENTS OPERATORS */

			reverse_iterator	&operator++() {
				--_current;
				return (*this);
			}
			reverse_iterator	&operator--() {
				++_current;
				return (*this);
			}

			reverse_iterator	operator++(int) {
				reverse_iterator	tmp(*this);
				--_current;
				return (tmp);
			}
			reverse_iterator	operator--(int) {
				reverse_iterator	tmp(*this);
				++_current;
				return (tmp);
			}

			reverse_iterator	operator+(difference_type n) const { return (reverse_iterator(_current - n)); }
			reverse_iterator	operator-(difference_type n) const { return (reverse_iterator(_current + n)); }

			template<class U>
			reverse_iterator	&operator+=(U n) { return (*this = *this + n); }
			template<class U>
			reverse_iterator	&operator-=(U n) { return (*this = *this - n); }
			/* --------- */
	};

	/* COMPARE OPERATORS */

	template<class T, class U>
	bool	operator==(const reverse_iterator<T> &Iter1, const reverse_iterator<U> &Iter2) { return (Iter1.base() == Iter2.base()); }
	template<class T, class U>
	bool	operator!=(const reverse_iterator<T> &Iter1, const reverse_iterator<U> &Iter2) { return !(Iter1 == Iter2); }
	template<class T, class U>
	bool	operator<(const reverse_iterator<T> &Iter1, const reverse_iterator<U> &Iter2) { return (Iter1.base() > Iter2.base()); }
	template<class T, class U>
	bool	operator<=(const reverse_iterator<T> &Iter1, const reverse_iterator<U> &Iter2) { return !(Iter2 < Iter1); }
	template<class T, class U>
	bool	operator>(const reverse_iterator<T> &Iter1, const reverse_iterator<U> &Iter2) { return (Iter2 < Iter1); }
	template<class T, class U>
	bool	operator>=(const reverse_iterator<T> &Iter1, const reverse_iterator<U> &Iter2) { return !(Iter1 < Iter2); }
	/* --------- */

	template<class T>
	reverse_iterator<T>	operator+(typename reverse_iterator<T>::difference_type n, const reverse_iterator<T> &Iter) { return (reverse_iterator<T>(Iter.base() - n)); }
	template<class T, class U>
	typename reverse_iterator<T>::difference_type	operator-(const reverse_iterator<T> &Iter1, const reverse_iterator<U> &Iter2) { return (Iter2.base() - Iter1.base()); }

}

#endif
