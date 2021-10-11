/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmunoz-f <mmunoz-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/30 17:32:07 by mmunoz-f          #+#    #+#             */
/*   Updated: 2021/10/11 20:39:15 by mmunoz-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __CONTAINERS_UTILS_H__
# define __CONTAINERS_UTILS_H__

namespace ft {

	/* is_integral redefinition */

	template<class T>
	struct	is_integral							{ static const bool value = false; };
	template<>
	struct	is_integral<bool>					{ static const bool value = true; };
	template<>
	struct	is_integral<char>					{ static const bool value = true; };
	template<>
	struct	is_integral<__char16_t>				{ static const bool value = true; };
	template<>
	struct	is_integral<__char32_t>				{ static const bool value = true; };
	template<>
	struct	is_integral<wchar_t>				{ static const bool value = true; };
	template<>
	struct	is_integral<signed char>			{ static const bool value = true; };
	template<>
	struct	is_integral<short int>				{ static const bool value = true; };
	template<>
	struct	is_integral<int>					{ static const bool value = true; };
	template<>
	struct	is_integral<long int>				{ static const bool value = true; };
	template<>
	struct	is_integral<long long int>			{ static const bool value = true; };
	template<>
	struct	is_integral<unsigned char>			{ static const bool value = true; };
	template<>
	struct	is_integral<unsigned short int>		{ static const bool value = true; };
	template<>
	struct	is_integral<unsigned int>			{ static const bool value = true; };
	template<>
	struct	is_integral<unsigned long int>		{ static const bool value = true; };
	template<>
	struct	is_integral<unsigned long long int>	{ static const bool value = true; };

	/* enable_if redefinition */

	template<bool B, class T = void>
	struct	enable_if;

	template<class T>
	struct	enable_if<true, T> { typedef T type; };

	/* struct traits for class in containers */

	/* iterators traits redefinition */

	template <class T>
	struct	iterator_traits {
		typedef	typename T::difference_type		difference_type;
		typedef	typename T::value_type			value_type;
		typedef	typename T::pointer				pointer;
		typedef	typename T::reference			reference;
		typedef	typename T::iterator_category	iterator_category;
	};

	template <class T>
	struct iterator_traits<T*> {
		typedef	ptrdiff_t						difference_type;
		typedef	T								value_type;
		typedef	T*								pointer;
		typedef	T&								reference;
		typedef	std::random_access_iterator_tag	iterator_category;
	};
	template <class T>
	struct iterator_traits<const T*> {
		typedef	ptrdiff_t						difference_type;
		typedef	T								value_type;
		typedef	const T*						pointer;
		typedef	const T&						reference;
		typedef	std::random_access_iterator_tag	iterator_category;
	};

	/* equal redefinition */

	template<class T, class U>
	bool	equal(T first1, T last1, U first2) {
		for (; first1 != last1; first1++, first2++) {
			if (!(*first1 == *first2))
				return (false);
		}
		return (true);
	}
	template<class T, class U, class BPred>
	bool	equal(T first1, T last1, U first2, BPred p) {
		for (; first1 != last1; first1++, first2++) {
			if (!(p(*first1, *first2)))
				return (false);
		}
		return (true);
	}

	/* lexicographical_compare redefinition */

	template<class T, class U>
	bool	lexicographical_compare(T first1, T last1, U first2, U last2) {
		for (; first1 != last1 && first2 != last2; first1++, first2++) {
			if (*first1 < *first2)
				return (true);
			if (*first1 > *first2)
				return (false);
		}
		return (first1 == last1 && first2 != last2);
	}
	template<class T, class U, class Comp>
	bool	lexicographical_compare(T first1, T last1, U first2, U last2, Comp c) {
		for (; first1 != last1 && first2 != last2; first1++, first2++) {
			if (c(*first1, *first2))
				return (true);
			if (c(*first2, *first1))
				return (false);
		}
		return (first1 == last1 && first2 != last2);
	}

	/* swap redefinition */

	template<class T>
	void	swap(T& a, T &b) {
		T	tmp;

		tmp = a;
		a = b;
		b = tmp;
	}

	/* distance redefinition */
	template<class InputIt>
	typename iterator_traits<InputIt>::difference_type	distance(InputIt first, InputIt last) {
		typename iterator_traits<InputIt>::difference_type	ret = 0;
		for (;first != last; first++, ret++);
		return (ret);
	}
}

#endif
