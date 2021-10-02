/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tests.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmunoz-f <mmunoz-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/02 02:53:37 by mmunoz-f          #+#    #+#             */
/*   Updated: 2021/10/02 05:20:39 by mmunoz-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __TEST_H__
# define __TEST_H__

# define RESET		"\033[0m"
# define BLACK		"\033[30m"
# define RED		"\033[31m"
# define GREEN		"\033[32m"
# define YELLOW		"\033[33m"
# define BLUE		"\033[34m"
# define MAGENTA	"\033[35m"
# define CYAN		"\033[36m"
# define WHITE		"\033[37m"
# define BOLDBLACK	"\033[1m\033[30m"

class	Simple {
	public:
		int	n;
};

template<class T>
typename ft::enable_if<ft::is_integral<T>::value, T>::type	ft_compile(T a) { return (a); }

template<class T>
bool	is_equal(T a, T b) { return (a == b); }
template<class T>
bool	less_than(T a, T b) { return (a < b); }

#endif
