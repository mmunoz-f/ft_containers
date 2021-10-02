/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pair.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmunoz-f <mmunoz-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/02 03:28:26 by mmunoz-f          #+#    #+#             */
/*   Updated: 2021/10/02 05:44:10 by mmunoz-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __PAIR_H__
# define __PAIR_H__

namespace ft{

/* pair redefinition */

	template<class T1, class T2>
	struct	pair {
		T1 first;
		T2 second;

		pair() {}
		pair(const T1 &x, const T2 &y) : first(x), second(y) {}
		pair(const pair<T1, T2> &p) : first(p.first), second(p.second) {}

		pair	&operator=(const pair<T1, T2> &p) {
			first(p.first);
			second(p.second);
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
	pair<T1, T2>	make_pair(T1 a, T2 b) {
		return (pair<T1, T2>(a, b));
	}

}

#endif
