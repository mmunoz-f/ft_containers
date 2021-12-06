/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_map_test.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmunoz-f <mmunoz-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 17:14:37 by mmunoz-f          #+#    #+#             */
/*   Updated: 2021/12/06 17:42:23 by mmunoz-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <list>
#include "../map.hpp"
#include "tests.hpp"

void	print_map(const ft::map<int, int> &a) {
	std::cout << "size: " << a.size() << ", max_size: " << a.max_size() << std::endl;
	for (ft::map<int, int>::const_iterator i = a.begin(); i != a.end(); i++)
		std::cout << i->first << " :: " << i->second << ", ";
	std::cout << std::endl;
}

int main(void) {

	std::cout << "<<< FT::MAP TEST >>>" << std::endl;

	{
		ft::map<int, int>	a;
		std::cout << "Empty contructor called" << std::endl;
		print_map(a);
		a.insert(ft::make_pair(21, 42));
		a.insert(ft::make_pair(42, 84));
		print_map(a);
		a.erase(42);
		print_map(a);
	}
	{
		std::list<ft::pair<int, int> >	lst;
		for (size_t i = 0; i < 100; i++)
			lst.push_back(ft::make_pair(i, i));

		std::allocator<ft::pair<int, int> >	alloc;
		ft::map<int, int> *a	= new ft::map<int, int>(lst.begin(), lst.end());
		ft::map<int, int>	b(*a);
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
	if (M_LEAKS)
		system("leaks ft_map_test");
	return (0);
}
