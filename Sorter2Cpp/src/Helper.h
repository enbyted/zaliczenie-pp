#pragma once
/**
* Licensed under MIT license (see LICENSE for details)
* Copyright (c) 2017 Bartosz Grabias
*/

#include <cstdlib>  /* rand */

//typedef unsigned int number_t;
typedef double number_t;
typedef StaticArray<number_t> array_t;

struct range_t
{
	const number_t start;
	const number_t end;
	const number_t range;

	range_t(number_t _start, number_t _end)
		: start(min(_start, _end))
		, end(max(_start, _end))
		, range(end - start + 1)
	{}
private:
	static constexpr number_t max(number_t a, number_t b)
	{
		return  (a > b) ? a : b;
	}
	static constexpr number_t min(number_t a, number_t b)
	{
		return  (a > b) ? b : a;
	}
};

template<typename T> static T random(const range_t& range)
{
	T value = 0;
	T accumulator = 0;

	while (accumulator < range.range)
	{
		value += rand();
		accumulator += RAND_MAX;
	}

	return range.start + (value % range.range);
}

template<> static float random<float>(const range_t& range)
{
	float value = (float)rand() / (float)(RAND_MAX + 1);
	return range.start + value * (range.range - 1);
}

template<> static double random<double>(const range_t& range)
{
	double value = (double)rand() / (double)(RAND_MAX + 1);
	return range.start + value * (range.range - 1);
}