/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_test.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmunoz-f <mmunoz-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 16:22:36 by mmunoz-f          #+#    #+#             */
/*   Updated: 2021/10/05 20:40:25 by mmunoz-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vector>
#include <iostream>

int	main(void) {

	{
		std::vector<int>	a;
		std::cout << "Empty constructor called" << std::endl;
		std::cout << "size: " << a.size() << ", capacity: " << a.capacity() <<  std::endl;
	}
	{
		std::vector<int>	a(5, 3);
		std::cout << "Contructor called with initial size a value" <<std::endl;
		std::cout << "size: " << a.size() << ", capacity: " << a.capacity() << ", max_size: " << a.max_size() << std::endl;
		for (size_t i = 0; i < a.size(); i++)
			std::cout << a[i] << ", ";
		std::cout << std::endl;
	}
}
