#include "../set.hpp"
#include <set>
#include <list>

using namespace std;

int	main (void) {
	std::list<int> lst;
	unsigned int lst_size = 400;
	for (unsigned int i = 0; i < lst_size; ++i)
		lst.push_back(lst_size - i);

	ft::set<int>	m(lst.begin(), lst.end());
	std::set<int>	n(lst.begin(), lst.end());

	for (;!m.empty() && !n.empty();) {
		ft::set<int>::const_iterator	it = m.begin();
		std::set<int>::const_iterator	ite = n.begin();

		for (;it != m.end() && ite != n.end();it++, ite++) {
			if (*it != *ite) {
				std::cout << "caca" << std::endl;
				return (1);
			}
		}
		if (it != m.end() || ite != n.end()) {
			std::cout << "caca" << std::endl;
			return (1);
		}
		m.erase(m.begin());
		n.erase(n.begin());
	}
	if (!m.empty() || !n.empty()) {
		std::cout << "caca" << std::endl;
		return (1);
	}
	return (0);
}
