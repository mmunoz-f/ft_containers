/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pruebas.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmunoz-f <mmunoz-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/30 18:56:55 by mmunoz-f          #+#    #+#             */
/*   Updated: 2021/10/02 02:22:00 by mmunoz-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <iterator>
#include <type_traits>

class Example {
	public:
		int	n;
};

int	main(void) {

	std::cout << std::is_integral<Example>::value << std::endl;
	std::cout << std::is_integral<int>::value << std::endl;
	return (0);
}
