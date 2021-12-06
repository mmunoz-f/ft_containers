/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   std_vector_test.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmunoz-f <mmunoz-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 16:37:19 by mmunoz-f          #+#    #+#             */
/*   Updated: 2021/12/06 19:38:32 by mmunoz-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <vector>
#include "tests.hpp"

void	print_vector(const std::vector<int> &a) {
	std::cout << "size: " << a.size() << ", capacity: " << a.capacity() << ", max_size: " << a.max_size() << std::endl;
		for (std::vector<int>::const_iterator i = a.begin(); i != a.end(); i++)
			std::cout << *i << ", ";
	std::cout << std::endl;
}

int	main(void) {

	std::cout << "<<< STD::VECTOR TEST >>>" << std::endl;

	{
		std::vector<int>	a;
		std::cout << "Empty constructor called" << std::endl;
		print_vector(a);
		a.push_back(10);
		a.push_back(5);
		print_vector(a);
		a.pop_back();
		print_vector(a);
	}
	{
		std::allocator<int>	alloc;
		std::vector<int>		a(alloc);
		std::cout << "Allocator constructor called" << std::endl;
		print_vector(a);
	}
	{
		std::vector<int>	a(3);
		std::cout << "Size constructor called" << std::endl;
		print_vector(a);
	}
	{
		std::vector<int>	a(5, 3);
		std::cout << "Contructor called with initial size a value" << std::endl;
		print_vector(a);
	}
	{
		std::vector<int>	tmp(5, 3);
		std::vector<int>	a(tmp.begin(), tmp.end());
		std::vector<int>	b;
		std::cout << "Range constructor called" << std::endl;
		print_vector(a);
		b = a;
		std::cout << "Assign operator callod" << std::endl;
		print_vector(b);
	}
	{
		std::vector<int>* tmp_ptr = new std::vector<int>;

		tmp_ptr->assign(10, 8);
		print_vector(*tmp_ptr);
		for (size_t	i = 0; i < 10; i++)
			tmp_ptr->at(i) -= 1;
		print_vector(*tmp_ptr);

		std::cout << "Copy constructor called" << std::endl;
		const std::vector<int>	a(*tmp_ptr);

		tmp_ptr->insert(tmp_ptr->end(), a.begin(), a.end());
		print_vector(*tmp_ptr);
		tmp_ptr->erase(++(++tmp_ptr->begin()));
		print_vector(*tmp_ptr);


		print_vector(a);

		*tmp_ptr != a ? std::cout << RED << "[KO] " : std::cout << GREEN << "[OK] ";
		*tmp_ptr == a ? std::cout << GREEN << "[OK] " : std::cout << RED << "[KO] ";
		std::cout << WHITE;
		std::cout << (*tmp_ptr < a ? "true " : "false ");
		std::cout << (*tmp_ptr > a ? "true " : "false ");
		std::cout << (*tmp_ptr <= a ? "true " : "false ");
		std::cout << (*tmp_ptr >= a ? "true " : "false ");
		std::cout << std::endl;

		tmp_ptr->clear();
		print_vector(*tmp_ptr);

		delete	tmp_ptr;
	}
	{
		std::vector<int>	a;
		std::vector<int>	b;

		for (size_t i = 0; i < 10; i++)
			a.push_back(i);
		print_vector(a);
		b.insert(b.begin(), a.rbegin(), a.rend());
		print_vector(b);
		swap(a, b);
		print_vector(a);
		print_vector(b);
	}
	return (0);
}
