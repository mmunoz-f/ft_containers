#include "../map.hpp"
#include <map>

using namespace std;

int	main (void) {
	ft::map<int, int>	m;
	ft::map<int, int>	n;

	m.insert(ft::make_pair(5,3));
	m.insert(ft::make_pair(2,3));
	m.insert(ft::make_pair(2,3));
	m.insert(ft::make_pair(2,3));
	m.insert(ft::make_pair(8,3));
	n.insert(ft::make_pair(3,3));
	n.insert(ft::make_pair(6,3));
	
	m.erase(8);

	m.print();
	n.print();

	std::cout << "====================" << std::endl;

	ft::swap(m, n);

	m.print();
	n.print();

	std::cout << std::endl;

	system("leaks a.out");

	return (0);
}
