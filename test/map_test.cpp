#include "../set.hpp"
#include <set>
#include <list>

using namespace std;

int	is_bad(ft::set<int> set, std::set<int> original) {
	std::cout << "Tienes derecho a llorar" << std::endl;
	set.print();
	ft::set<int>	n(original.begin(), original.end());
	n.print();
	return (1);
}

int	main (void) {

	std::list<int> lst;
	unsigned int lst_size = 3;
	for (unsigned int i = 0; i < lst_size; ++i)
		lst.push_back(lst_size - i);

	ft::set<int>	a(lst.begin(), lst.end());

	return 0;

	ft::set<int>	m(lst.begin(), lst.end());
	std::set<int>	n(lst.begin(), lst.end());

	for (;!m.empty() && !n.empty();) {
		ft::set<int>::const_iterator	it = m.begin();
		std::set<int>::const_iterator	ite = n.begin();

		for (;it != m.end() && ite != n.end();it++, ite++) {
			if (*it != *ite)
				return (is_bad(m, n));
		}
		if (it != m.end() || ite != n.end())
			return (is_bad(m, n));
		m.erase(m.begin());
		n.erase(n.begin());
	}
	if (!m.empty() || !n.empty())
		return (is_bad(m, n));
	return (0);
}
