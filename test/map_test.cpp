#include "../map.hpp"
#include <map>

int	main (void) {
	ft::map<int, int>	m;
	std::map<int, int>	n;

	m.insert(ft::make_pair(14,3));
	m.insert(ft::make_pair(75,3));
	m.insert(ft::make_pair(33,3));
	m.insert(ft::make_pair(24,3));
	m.insert(ft::make_pair(11,3));
	m.insert(ft::make_pair(8,3));
	m.insert(ft::make_pair(-8,3));
	m.insert(ft::make_pair(12,3));
	m.insert(ft::make_pair(13,3));

	m.print();
	std::cout << "Count: " << m.count(12) << std::endl;
	return (0);
}
