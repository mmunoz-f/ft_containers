/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   std_map_test.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmunoz-f <mmunoz-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 17:43:04 by mmunoz-f          #+#    #+#             */
/*   Updated: 2021/12/06 17:45:06 by mmunoz-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <map>
#include <list>
#include "tests.hpp"

void	print_map(const std::map<int, int> &a) {
	std::cout << "size: " << a.size() << ", max_size: " << a.max_size() << std::endl;
	for (std::map<int, int>::const_iterator i = a.begin(); i != a.end(); i++)
		std::cout << i->first << " :: " << i->second << ", ";
	std::cout << std::endl;
}

int main(void) {

	std::cout << "<<< FT::MAP TEST >>>" << std::endl;

	{
		std::map<int, int>	a;
		std::cout << "Empty contructor called" << std::endl;
		print_map(a);
		a.insert(std::make_pair(21, 42));
		a.insert(std::make_pair(42, 84));
		print_map(a);
		a.erase(42);
		print_map(a);
	}
	{
		std::list<std::pair<int, int> >	lst;
		for (size_t i = 0; i < 100; i++)
			lst.push_back(std::make_pair(i, i));

		std::allocator<std::pair<int, int> >	alloc;
		std::map<int, int> *a	= new std::map<int, int>(lst.begin(), lst.end());
		std::map<int, int>	b(*a);
		std::cout << "Range contructor called" << std::endl;
		print_map(*a);
		std::cout << "Copy construct called" << std::endl;
		print_map(b);

		b.erase(b.find(10), b.find(20));
		print_map(b);

		swap(*a, b);
		print_map(*a);
		print_map(b);

		*a == b ? std::cout << RED << "[KO] " : std::cout << GREEN << "[OK] ";
		*a != b ? std::cout << GREEN << "[OK] " : std::cout << RED << "[KO] ";
		std::cout << WHITE;
		std::cout << (*a < b ? "true " : "false ");
		std::cout << (*a > b ? "true " : "false ");
		std::cout << (*a <= b ? "true " : "false ");
		std::cout << (*a >= b ? "true " : "false ");
		std::cout << std::endl;

		delete a;

		std::cout << (b.lower_bound(60))->first << std::endl;
		std::cout << (b.upper_bound(60))->first << std::endl;
		std::cout << (b.equal_range(60)).first->first << " :: " << (b.equal_range(60)).first->first << std::endl;

		b.clear();
		print_map(b);
	}
	return (0);
}