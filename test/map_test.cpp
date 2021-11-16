#include "../map.hpp"

int	main (void) {
	ft::map<int, int>	m;

	m.insert(ft::make_pair(12,3));
	m.insert(ft::make_pair(2,3));
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
	return (0);
}
