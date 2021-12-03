#ifndef BENCHMARKS_HPP

#	include <ctime>

class Timer
{

	std::clock_t _start;

public:
	Timer();
	Timer(const Timer &ref);
	Timer &operator=(const Timer &ref);
	~Timer();
	void start();
	std::clock_t stop();
};

#	include "../../vector.hpp"
#	include "../../stack.hpp"
#	include "../../set.hpp"
#	include "../../map.hpp"
#	include <iostream>
#	include <map>
#	include <stack>
#	include <vector>
#	include <set>

// mapType must be a map to int, bool.
template <typename MapType>
std::clock_t insert_growing(size_t times, MapType map)
{
	Timer t;
	t.start();

	for (size_t i = 0; i < times; i++)
	{
		map[i] = true; // insert a constantly growing range of integers
		// which is a worst-case scenario for an unbalanced map.
		map.find(i);
	}

	// Copy-construction and destruction
	{
		MapType new_map(map);
	}

	return t.stop();
}

// mapType must be a map to int, bool.
template <typename SetType>
std::clock_t se_insert_growing(size_t times, SetType set)
{
	Timer t;
	t.start();

	for (size_t i = 0; i < times; i++)
	{
		set.insert(i); // insert a constantly growing range of integers
		// which is a worst-case scenario for an unbalanced map.
		set.find(i);
	}

	// Copy-construction and destruction
	{
		SetType new_set(set);
	}

	return t.stop();
}

// Vector benchmark
// Vector must be a vector of ints
template <typename VectorType>
std::clock_t v_insert_growing(size_t times, VectorType vector)
{
	Timer t;
	t.start();

	int tmp = 0;

	for (size_t i = 0; i < times; i++)
	{
		vector.push_back(i); // insert a constantly growing range of integers
		tmp = vector[i];
	}

	{

		VectorType newVector(vector); // copy and destruction
	}

	vector.erase(vector.begin(), vector.end()); // erase

	return t.stop();
}

template <typename StackType>
std::clock_t s_insert_growing(size_t times, StackType stack)
{
	Timer t;
	t.start();

	int tmp = 0;

	for (size_t i = 0; i < times; i++)
	{
		stack.push(i); // insert a constantly growing range of integers
	}

	{
		StackType newStack(stack); //copy and destruction
	}

	for (size_t i = 0; i < times; i++)
	{
		tmp = stack.top();
		stack.pop();
	}

	return t.stop();
}

void benchmark_vector();
void benchmark_stack();
void benchmark_map();
void benchmark_set();
#endif // !BENCHMARKS_HPP
