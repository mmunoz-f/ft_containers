/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vector_test.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmunoz-f <mmunoz-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 16:22:36 by mmunoz-f          #+#    #+#             */
/*   Updated: 2021/10/07 20:43:02 by mmunoz-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../vector.hpp"
#include <iostream>

int	main(void) {

	std::cout << "<<< FT::VECTOR TEST >>>" << std::endl;

	{
		ft::vector<int>	a;
		std::cout << "Empty constructor called" << std::endl;
		std::cout << "size: " << a.size() << ", capacity: " << a.capacity() << ", max_size: " << a.max_size() << std::endl;
		for (ft::vector<int>::iterator i = a.begin(); i != a.end(); i++)
			std::cout << *i << ", ";
		a.push_back(10);
		for (ft::vector<int>::iterator i = a.begin(); i != a.end(); i++)
			std::cout << *i << ", ";
		std::cout << std::endl;
	}
	/*
	{
		std::allocator<int>	alloc;
		ft::vector<int>		a(alloc);
		std::cout << "Allocator constructor called" << std::endl;
		std::cout << "size: " << a.size() << ", capacity: " << a.capacity() << ", max_size: " << a.max_size() << std::endl;
		for (ft::vector<int>::iterator i = a.begin(); i != a.end(); i++)
			std::cout << *i << ", ";
		std::cout << std::endl;
	}
	{
		ft::vector<int>	a(3);
		std::cout << "Size constructor called" << std::endl;
		std::cout << "size: " << a.size() << ", capacity: " << a.capacity() << ", max_size: " << a.max_size() << std::endl;
		for (ft::vector<int>::iterator i = a.begin(); i != a.end(); i++)
			std::cout << *i << ", ";
		std::cout << std::endl;
	}
	{
		ft::vector<int>	a(5, 3);
		std::cout << "Contructor called with initial size a value" <<std::endl;
		std::cout << "size: " << a.size() << ", capacity: " << a.capacity() << ", max_size: " << a.max_size() << std::endl;
		for (ft::vector<int>::iterator i = a.begin(); i != a.end(); i++)
			std::cout << *i << ", ";
		std::cout << std::endl;
	}
	{
		ft::vector<int>	tmp(5, 3);
		ft::vector<int>	a(tmp);
		std::cout << "Copy constructor called" <<std::endl;
		std::cout << "size: " << a.size() << ", capacity: " << a.capacity() << ", max_size: " << a.max_size() << std::endl;
		for (ft::vector<int>::iterator i = a.begin(); i != a.end(); i++)
			std::cout << *i << ", ";
		std::cout << std::endl;
	}
	{
		ft::vector<int>	tmp(5, 3);
		ft::vector<int>	a(tmp.begin(), tmp.end());
		std::cout << "Range constructor called" <<std::endl;
		std::cout << "size: " << a.size() << ", capacity: " << a.capacity() << ", max_size: " << a.max_size() << std::endl;
		for (size_t i = 0; i < a.size(); i++)
			std::cout << a[i] << ", ";
		std::cout << std::endl;
	}
	*/
}
