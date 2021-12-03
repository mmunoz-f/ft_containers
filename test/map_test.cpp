#include "../set.hpp"
#include <map>
#include <list>

using namespace std;

int	main (void) {
	ft::set<int>	n;

	std::list<int> lst;
	unsigned int lst_size = 3;
	for (unsigned int i = 0; i < lst_size; ++i)
		lst.push_back(lst_size - i);

	ft::set<int>	m(lst.begin(), lst.end());

	m.print();

	return (0);
}
