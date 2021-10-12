#include "benchmarks.hpp"

Timer::Timer()
{
	_start = 0;
}

Timer::~Timer()
{
}

void Timer::start()
{
	_start = std::clock();
}

std::clock_t Timer::stop()
{
	return std::clock() - _start;
}

Timer::Timer(const Timer &ref)
{
	_start = ref._start;
}

Timer &Timer::operator=(const Timer &ref)
{
	_start = ref._start;
	return (*this);
}

// void benchmark_map()
// {
// 	std::cout << "\033[1;34m--- MAP BENCHMARK ⚡ ---\033[0m" << std::endl;
// 	std::clock_t std;
// 	std::clock_t ft;

// 	std::map<int, bool> sm1;
// 	ft::map<int, bool> m1;

// 	std = insert_growing(200000, sm1);
// 	std::cout << "Std: " << std << std::endl;
// 	ft = insert_growing(200000, m1);
// 	std::cout << "Ft: " << ft << std::endl;

// 	std::cout << "Our map is " << (double)ft / (double)std << " times slower.   ";

// 	if (((double)ft / (double)std) < 20.0)
// 	{
// 		std::cout << "\033[1;32m[PASS]\033[0m" << std::endl;
// 	}
// 	else
// 	{
// 		std::cout << "\033[1;31m[FAIL]\033[0m" << std::endl;
// 	}

// 	std::cout << std::endl;
// }

// void benchmark_set()
// {
// 	std::cout << "\033[1;34m--- SET BENCHMARK ⚡ ---\033[0m" << std::endl;
// 	std::clock_t std;
// 	std::clock_t ft;

// 	std::set<int> sm1;
// 	ft::set<int> m1;

// 	std = se_insert_growing(200000, sm1);
// 	std::cout << "Std: " << std << std::endl;
// 	ft = se_insert_growing(200000, m1);
// 	std::cout << "Ft: " << ft << std::endl;

// 	std::cout << "Our set is " << (double)ft / (double)std << " times slower.   ";

// 	if (((double)ft / (double)std) < 20.0)
// 	{
// 		std::cout << "\033[1;32m[PASS]\033[0m" << std::endl;
// 	}
// 	else
// 	{
// 		std::cout << "\033[1;31m[FAIL]\033[0m" << std::endl;
// 	}

// 	std::cout << std::endl;
// }

void benchmark_vector()
{
	std::cout << "\033[1;34m--- VECTOR BENCHMARK ⚡ ---\033[0m" << std::endl;
	std::clock_t std;
	std::clock_t ft;

	std::vector<int> sv1;
	ft::vector<int> v1;

	std = v_insert_growing(20000, sv1);
	std::cout << "Std: " << std << std::endl;
	ft = v_insert_growing(20000, v1);
	std::cout << "Ft: " << ft << std::endl;

	std::cout << "Our vector is " << (double)ft / (double)std << " times slower. ";

	if (((double)ft / (double)std) < 20.0)
	{
		std::cout << "\033[1;32m[PASS]\033[0m" << std::endl;
	}
	else
	{
		std::cout << "\033[1;31m[FAIL]\033[0m" << std::endl;
	}

	std::cout << std::endl;
}

// void benchmark_stack()
// {
// 	std::cout << "\033[1;34m--- STACK BENCHMARK ⚡ ---\033[0m" << std::endl;
// 	std::clock_t std;
// 	std::clock_t ft;

// 	std::stack<int> st1;
// 	ft::stack<int> s1;

// 	std = s_insert_growing(200000, st1);
// 	std::cout << "Std: " << std << std::endl;
// 	ft = s_insert_growing(200000, s1);
// 	std::cout << "Ft: " << ft << std::endl;

// 	std::cout << "Our stack is " << (double)ft / (double)std << " times slower. ";

// 	if (((double)ft / (double)std) < 20.0)
// 	{
// 		std::cout << "\033[1;32m[PASS]\033[0m" << std::endl;
// 	}
// 	else
// 	{
// 		std::cout << "\033[1;31m[FAIL]\033[0m" << std::endl;
// 	}

// 	std::cout << std::endl;
// }
