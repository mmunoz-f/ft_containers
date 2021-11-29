#include "../map.hpp"
#include <map>

int	main (void) {
	ft::map<int, int>	m;

	m.insert(ft::make_pair(5,3));
	m.insert(ft::make_pair(2,3));

	m.print();
	std::cout << "Count: " << m.size() << std::endl;

	std::cout << "========================" << std::endl;

	m.erase(m.begin(), m.end());
	m.print();
	std::cout << "Count: " << m.size() << std::endl;

	return (0);
}
