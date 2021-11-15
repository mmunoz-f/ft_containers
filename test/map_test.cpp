#include "../map.hpp"

int	main (void) {
	ft::map<int, int>	m;

	m.insert(ft::make_pair(12,3));
	m.print();
	return (0);
}
