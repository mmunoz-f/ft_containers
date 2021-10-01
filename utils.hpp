/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmunoz-f <mmunoz-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/30 17:32:07 by mmunoz-f          #+#    #+#             */
/*   Updated: 2021/10/01 20:19:44 by mmunoz-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __CONTAINERS_UTILS_H__
# define __CONTAINERS_UTILS_H__

namespace ft {

	/* is_integral redefinition */

	template<class T>
	struct	is_integral;
	struct	is_integral<bool> { bool value = true ; };
	struct	is_integral<char> { bool value = true ; };
	struct	is_integral<__char16_t> { bool value = true ; };
	struct	is_integral<__char32_t> { bool value = true ; };
	struct	is_integral<wchar_t> { bool value = true ; };
	struct	is_integral<signed char> { bool value = true ; };
	struct	is_integral<short int> { bool value = true ; };
	struct	is_integral<int> { bool value = true ; };
	struct	is_integral<long int> { bool value = true ; };
	struct	is_integral<long long int> { bool value = true ; };
	struct	is_integral<unsigned char> { bool value = true ; };
	struct	is_integral<unsigned short int> { bool value = true ; };
	struct	is_integral<unsigned int> { bool value = true ; };
	struct	is_integral<unsigned long int> { bool value = true ; };
	struct	is_integral<unsigned long long int> { bool value = true ; };

	/* enable_if redefinition */

	template<bool B, class T>
	struct	enable_if;

	template<class T>
	struct	enable_if<true, T> { typedef T type; };

	/* pair redefinition */

	template<class T1, class T2>
	struct	pair { typedef T1 first; typedef T2 second; };

	template<class T1, class T2>
	struct	pair	make_pair(T1 a, T2 b) {
		return (pair<a, b>);
	}

	/* iterators traits redefinition */

	template <class T>
	struct	iterator_traits {
		typedef	T::difference_type		difference_type;
		typedef	T::value_type			value_type;
		typedef	T::pointer				pointer;
		typedef	T::reference			reference;
		typedef	T::iterator_category	iterator_category;
	};

	template <class T>
	struct iterator_traits<T*> {
		typedef	ptrdiff_t						difference_type;
		typedef	T								value_type;
		typedef	T*								pointer;
		typedef	T&								reference;
		typedef	std::random_acces_iterator_tag	iterator_categoty;
	};
	template <class T>
	struct iterator_traits<const T*> {
		typedef	ptrdiff_t						difference_type;
		typedef	T								value_type;
		typedef	const T*						pointer;
		typedef	const T&						reference;
		typedef	std::random_acces_iterator_tag	iterator_categoty;
	};

	/* Reverse iterator reimplementation */

	template<class T>
	class	reverse_iterator {
		protected:
			Iterator	_current;
		public:
			typedef typename ft::iterator_traits<T>::iterator_category	iterator_categoty;
			typedef typename ft::iterator_traits<T>::value_type			value_type;
			typedef typename ft::iterator_traits<T>::difference_type	difference_type;
			typedef typename ft::iterator_traits<T>::pointer			pointer;
			typedef typename ft::iterator_traits<T>::reference			reference;

			reverse_iterator() : _current() {}
			explicit	reverse_iterator(T x) : _current(x) {}
			template<class U>
			reverse_iterator(const reverse_iterator<U> &other) : _current(other.base()) {}

			template<class U>
			reverse_iterator	&operator=(const reverse_iterator<U> &other) {
				_current = other.base();
				return (*this);
			}

			T	base() const { return (_current); }

			reference	operator*() const { return (*_current); }
			reference	operator->() const { return (*_current); }

			reference	operator[](difference_type n) const { return (_current[ -n - 1]); }

			reverse_iterator	&operator++() {
				--_current;
				return (*this);
			}
			reverse_iterator	&operator--() {
				++_current;
				return (*this);
			}

			reverse_iterator	operator++(int) {
				reverse_iterator	tmp(this);
				--_current;
				return (tmp);
			}
			reverse_iterator	operator--(int) {
				reverse_iterator	tmp(this);
				++_current;
				return (tmp);
			}

			template<class U>
			reverse_iterator	operator+(U n) const { return (reverse_iterator(base() - n)); }
			template<class U>
			reverse_iterator	operator-(U n) const { return (reverse_iterator(base() + n)); }

			template<class U>
			reverse_iterator	&operator+=(U n) { return (*this = *this + n); }
			template<class U>
			reverse_iterator	&operator-=(U n) { return (*this = *this - n); }
	};

	template<class T, class U>
	bool	operator==(const reverse_iterator<T> &Iter1, const reverse_iterator<U> &Iter2) { return (Iter1.base() == Iter2.base); }
	template<class T, class U>
	bool	operator!=(const reverse_iterator<T> &Iter1, const reverse_iterator<U> &Iter2) { return (Iter1.base() != Iter2.base()) }
	template<class T, class U>
	bool	operator<(const reverse_iterator<T> &Iter1, const reverse_iterator<U> &Iter2) { return (Iter1.base() < Iter2.base()) }
	template<class T, class U>
	bool	operator<=(const reverse_iterator<T> &Iter1, const reverse_iterator<U> &Iter2) { return (Iter1.base() <= Iter2.base()) }
	template<class T, class U>
	bool	operator>(const reverse_iterator<T> &Iter1, const reverse_iterator<U> &Iter2) { return (Iter1.base() > Iter2.base()) }
	template<class T, class U>
	bool	operator>=(const reverse_iterator<T> &Iter1, const reverse_iterator<U> &Iter2) { return (Iter1.base() >= Iter2.base()) }

	template<class T>
	typename reverse_iterator<T>::difference_type	&operator+(const reverse_iterator<T> &Iter1, const reverse_iterator<T> &Iter2) { return (Iter1.base() + Iter2.base()) }
	template<class T>
	typename reverse_iterator<T>::difference_type	&operator-(const reverse_iterator<T> &Iter1, const reverse_iterator<T> &Iter2) { return (Iter1.base() - Iter2.base()) }

	/* equal redefinition */

	template<class T, class U>
	bool	equal(T first1, T last1, U first2) {
		for (; first1 != last1; first1++, first2++) {
			if (!*first1 == *first2)
				return (false);
		}
		return (true);
	}
	template<class T, class U, class BPred>
	bool	equal(T first1, T last1, U first2, BPred p) {
		for (; first1 != last1 && first2!= last2; first1++, first2++) {
			if (!p(*first1, *first2))
				return (false);
		}
		return (true);
	}

	/* lexicographical_compare redefinition */

	template<class T, class U>
	bool	lexicographical_compare(T first1, T last1, U first2, U last2) {
		for (; first1 < last1; first1++, first2++) {
			if (*first1 > *first2)

		}
		return (true);
	}
	template<class T, class U, class Comp>
	bool	lexicographical_compare(T first1, T last1, U first2, U last2, Comp c) {
		for (; first1 < last1; first1++, first2++) {
			if (*first1 < *first2)

		}
	}
}

#endif
