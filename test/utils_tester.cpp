/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_tester.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmunoz-f <mmunoz-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/02 01:22:04 by mmunoz-f          #+#    #+#             */
/*   Updated: 2021/10/02 06:20:57 by mmunoz-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <vector>
#include <string>
#include "../utils/utils.hpp"
#include "../utils/pair.hpp"
#include "../utils/reverse_iterator.hpp"
#include "tests.hpp"

int	main(void) {

	std::cout << " ---- Testing utils.hpp ----" << std::endl << std::endl;

	std::cout << "-- is_integral --" << std::endl;
	ft::is_integral<float>::value ? (std::cout << RED << "[KO] ") : (std::cout << GREEN << "[OK] ");
	ft::is_integral<Simple>::value ? (std::cout << RED << "[KO] ") : (std::cout << GREEN << "[OK] ");
	ft::is_integral<bool>::value ? (std::cout << GREEN << "[OK] ") : (std::cout << RED << "[KO] ");
	ft::is_integral<char>::value ? (std::cout << GREEN << "[OK] ") : (std::cout << RED << "[KO] ");
	ft::is_integral<__char16_t>::value ? (std::cout << GREEN << "[OK] ") : (std::cout << RED << "[KO] ");
	ft::is_integral<__char32_t>::value ? (std::cout << GREEN << "[OK] ") : (std::cout << RED << "[KO] ");
	ft::is_integral<wchar_t>::value ? (std::cout << GREEN << "[OK] ") : (std::cout << RED << "[KO] ");
	ft::is_integral<signed char>::value ? (std::cout << GREEN << "[OK] ") : (std::cout << RED << "[KO] ");
	ft::is_integral<short int>::value ? (std::cout << GREEN << "[OK] ") : (std::cout << RED << "[KO] ");
	ft::is_integral<int>::value ? (std::cout << GREEN << "[OK] ") : (std::cout << RED << "[KO] ");
	ft::is_integral<long long int>::value ? (std::cout << GREEN << "[OK] ") : (std::cout << RED << "[KO] ");
	ft::is_integral<unsigned char>::value ? (std::cout << GREEN << "[OK] ") : (std::cout << RED << "[KO] ");
	ft::is_integral<unsigned short int>::value ? (std::cout << GREEN << "[OK] ") : (std::cout << RED << "[KO] ");
	ft::is_integral<unsigned int>::value ? (std::cout << GREEN << "[OK] ") : (std::cout << RED << "[KO] ");
	ft::is_integral<unsigned long int>::value ? (std::cout << GREEN << "[OK] ") : (std::cout << RED << "[KO] ");
	ft::is_integral<unsigned long long int>::value ? (std::cout << GREEN << "[OK] ") : (std::cout << RED << "[KO] ");
	std::cout << WHITE << std::endl << std::endl;

	std::cout << "-- enable_if --" << std::endl;
	{
		bool	a = true;

		/* Compiles */
		if (::ft_compile(a))
			std::cout << "Compiles!!" << std::endl;
		/* Does not compile */
		//	Simple	b;
		//	::ft_compile(b);
		std::cout << std::endl;
	}

	std::cout << "-- equal --" << std::endl;
	{
		std::vector<int> a;
		std::vector<int> b;
		for (int i = 0; i < 5; i++) {
			a.push_back(i);
			b.push_back(i);
		}

		ft::equal(a.begin(), a.end(), b.begin()) ? (std::cout << GREEN << "[OK] ") : (std::cout << RED << "[KO] ");
		ft::equal(a.begin(), a.end(), b.begin(), ::is_equal<int>) ? (std::cout << GREEN << "[OK] ") : (std::cout << RED << "[KO] ");
		b[2]++;
		ft::equal(a.begin(), a.end(), b.begin()) ? (std::cout << RED << "[KO] ") : (std::cout << GREEN << "[OK] ");
		ft::equal(a.begin(), a.end(), b.begin(), ::is_equal<int>) ? (std::cout << RED << "[KO] ") : (std::cout << GREEN << "[OK] ");
		std::cout << WHITE << std::endl << std::endl;
	}

	std::cout << "-- lexicografical_compare --" <<std::endl;
	{
		std::vector<int> a;
		std::vector<int> b;
		std::vector<int> c;
		for (int i = 0; i < 5; i++) {
			a.push_back(i);
			b.push_back(i);
			if (i < 4)
				c.push_back(i);
		}
		ft::lexicographical_compare(a.begin(), a.end(), b.begin(), b.end()) ? (std::cout << RED << "[KO] ") : (std::cout << GREEN << "[OK] ");
		ft::lexicographical_compare(a.begin(), a.end(), b.begin(), b.end(), ::less_than<int>) ? (std::cout << RED << "[KO] ") : (std::cout << GREEN << "[OK] ");
		b[2]++;
		ft::lexicographical_compare(a.begin(), a.end(), b.begin(), b.end()) ? (std::cout << GREEN << "[OK] ") : (std::cout << RED << "[KO] ");
		ft::lexicographical_compare(a.begin(), a.end(), b.begin(), b.end(), ::less_than<int>) ? (std::cout << GREEN << "[OK] ") : (std::cout << RED << "[KO] ");
		a[1]++;
		ft::lexicographical_compare(a.begin(), a.end(), b.begin(), b.end()) ? (std::cout << RED << "[KO] ") : (std::cout << GREEN << "[OK] ");
		ft::lexicographical_compare(a.begin(), a.end(), b.begin(), b.end(), ::less_than<int>) ? (std::cout << RED << "[KO] ") : (std::cout << GREEN << "[OK] ");
		c[1]++;
		ft::lexicographical_compare(a.begin(), a.end(), c.begin(), c.end()) ? (std::cout << RED << "[KO] ") : (std::cout << GREEN << "[OK] ");
		ft::lexicographical_compare(a.begin(), a.end(), c.begin(), c.end(), ::less_than<int>) ? (std::cout << RED << "[KO] ") : (std::cout << GREEN << "[OK] ");
		std::cout << WHITE <<std::endl << std::endl;
	}

	std::cout << "-- pairs --" << std::endl;
	{
		struct ft::pair<int, std::string>	a = ft::make_pair(1, std::string("hola"));
		struct ft::pair<int, std::string>	b(2, std::string("mundo"));
		struct ft::pair<int, std::string>	c(b);

		//std::cout << a.first << ": " << a.second << std::endl;
		//std::cout << b.first << ": " << b.second << std::endl;
		//std::cout << c.first << ": " << c.second << std::endl;

		c == b ? (std::cout << GREEN << "[OK] ") : (std::cout << RED << "[KO] ");
		c != b ? (std::cout << RED << "[KO] ") : (std::cout << GREEN << "[OK] ");
		c.first = 1;
		c < b ? (std::cout << GREEN << "[OK] ") : (std::cout << RED << "[KO] ");
		c > b ? (std::cout << RED << "[KO] ") : (std::cout << GREEN << "[OK] ");
		a < c ? (std::cout << GREEN << "[OK] ") : (std::cout << RED << "[KO] ");
		a > c ? (std::cout << RED << "[KO] ") : (std::cout << GREEN << "[OK] ");
		a <= c ? (std::cout << GREEN << "[OK] ") : (std::cout << RED << "[KO] ");
		a >= c ? (std::cout << RED << "[KO] ") : (std::cout << GREEN << "[OK] ");
		std::cout << WHITE <<std::endl << std::endl;
	}

	std::cout << "-- reverse_iterator --" << std::endl;
	{
		std::vector<int>	a;
		for (int i = 0; i < 5; i++)
			a.push_back(i);

		ft::reverse_iterator<int *>	r(a.end());
	}
	return (0);
}
