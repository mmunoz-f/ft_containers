/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pruebas.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmunoz-f <mmunoz-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/30 18:56:55 by mmunoz-f          #+#    #+#             */
/*   Updated: 2021/11/18 09:18:18 by mmunoz-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <iterator>
#include <type_traits>
#include <map>

class Example {
	public:
		int	n;
};

int	main(void) {
	std::map<int, int> m;

	std::map<int, int>::iterator	i = m.begin();

	return (0);
}
