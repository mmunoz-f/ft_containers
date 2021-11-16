/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pair.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmunoz-f <mmunoz-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/02 03:28:26 by mmunoz-f          #+#    #+#             */
/*   Updated: 2021/11/16 20:06:27 by mmunoz-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __PAIR_H__
# define __PAIR_H__

# include "utils.hpp"

#include <utility>

namespace ft{

/* pair redefinition */

	template<class T1, class T2>
	struct	pair {
		typedef T1	first_type;
		typedef T2	second_type;

		first_type first;
		second_type second;

		pair() : first(), second() {}
		pair(const first_type &x, const second_type &y) : first(x), second(y) {}
		template<class U1, class U2>
		pair(const pair<U1, U2> &p) : first(p.first), second(p.second) {}
		virtual	~pair () {}

		pair	&operator=(const pair &p) {
			first = p.first;
			second = p.second;
			return (*this);
		}
	};

	/* Non-member functions */

	template <class T1, class T2>
	bool operator==(const pair<T1,T2> &a, const pair<T1,T2> &b) { return a.first == b.first && a.second == b.second; }
	template <class T1, class T2>
	bool operator!=(const pair<T1,T2> &a, const pair<T1,T2> &b) { return !(a == b); }
	template <class T1, class T2>
	bool operator<(const pair<T1,T2> &a, const pair<T1,T2> &b) { return a.first < b.first || (!(b.first < a.first) && a.second < b.second); }
	template <class T1, class T2>
	bool operator<=(const pair<T1,T2> &a, const pair<T1,T2> &b) { return !(b < a); }
	template <class T1, class T2>
	bool operator>(const pair<T1,T2> &a, const pair<T1,T2> &b) { return b < a; }
	template <class T1, class T2>
	bool operator>=(const pair<T1,T2> &a, const pair<T1,T2> &b) { return !(a < b); }

	template<class T1, class T2>
	pair<T1, T2>	make_pair(const T1 &a, const T2 &b) {
		return (pair<T1, T2>(a, b));
	}
}

#endif
