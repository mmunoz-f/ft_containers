#include "benchmarks.hpp"
#include <unistd.h>

int main(void)
{
	std::cout << "Benchmarks: " << std::endl
			  << std::endl;

	benchmark_vector();
	benchmark_stack();
	benchmark_map();
	benchmark_set();
	
	system("leaks a.out");
}
