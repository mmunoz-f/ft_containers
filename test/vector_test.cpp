/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_test.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmunoz-f <mmunoz-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 16:22:36 by mmunoz-f          #+#    #+#             */
/*   Updated: 2021/10/07 20:33:20 by mmunoz-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vector>
#include <iostream>

int	main(void) {

	std::cout << "<<< STD::VECTOR TEST >>>" << std::endl;

	{
		std::vector<int>	a;
		std::cout << "Empty constructor called" << std::endl;
		std::cout << "size: " << a.size() << ", capacity: " << a.capacity() << ", max_size: " << a.max_size() << std::endl;
		for (std::vector<int>::iterator i = a.begin(); i != a.end(); i++)
			std::cout << *i << ", ";
		std::cout << std::endl;
	}
	{
		std::allocator<int>	alloc;
		std::vector<int>		a(alloc);
		std::cout << "Allocator constructor called" << std::endl;
		std::cout << "size: " << a.size() << ", capacity: " << a.capacity() << ", max_size: " << a.max_size() << std::endl;
		for (std::vector<int>::iterator i = a.begin(); i != a.end(); i++)
			std::cout << *i << ", ";
		std::cout << std::endl;
	}
	{
		std::vector<int>	a(3);
		std::cout << "Allocator constructor called" << std::endl;
		std::cout << "size: " << a.size() << ", capacity: " << a.capacity() << ", max_size: " << a.max_size() << std::endl;
		for (std::vector<int>::iterator i = a.begin(); i != a.end(); i++)
			std::cout << *i << ", ";
		std::cout << std::endl;
	}
	{
		std::vector<int>	a(5, 3);
		std::cout << "Contructor called with initial size a value" <<std::endl;
		std::cout << "size: " << a.size() << ", capacity: " << a.capacity() << ", max_size: " << a.max_size() << std::endl;
		for (std::vector<int>::iterator i = a.begin(); i != a.end(); i++)
			std::cout << *i << ", ";
		std::cout << std::endl;
	}
	{
		std::vector<int>	tmp(5, 3);
		std::vector<int>	a(tmp);
		std::cout << "Copy constructor called" <<std::endl;
		std::cout << "size: " << a.size() << ", capacity: " << a.capacity() << ", max_size: " << a.max_size() << std::endl;
		for (std::vector<int>::iterator i = a.begin(); i != a.end(); i++)
			std::cout << *i << ", ";
		std::cout << std::endl;
	}
	{
		std::vector<int>	tmp(5, 3);
		std::vector<int>	a(tmp.begin(), tmp.end());
		std::cout << "Range constructor called" <<std::endl;
		std::cout << "size: " << a.size() << ", capacity: " << a.capacity() << ", max_size: " << a.max_size() << std::endl;
		for (std::vector<int>::iterator i = a.begin(); i != a.end(); i++)
			std::cout << *i << ", ";
		std::cout << std::endl;
	}
}
