#include "../set.hpp"
#include <map>
#include <list>

using namespace std;

int	main (void) {
	ft::set<int>	n;

	std::list<int> lst;
	unsigned int lst_size = 7;
	for (unsigned int i = 0; i < lst_size; ++i)
		lst.push_back(lst_size - i);

	ft::set<int>	m(lst.begin(), lst.end());
	

	m.print();

	std::cout << "====================" << std::endl;

	m.erase(1);
	m.erase(2);
	m.erase(4);
	m.erase(5);
	m.erase(3);
	m.print();

	std::cout << std::endl;


	return (0);
}
