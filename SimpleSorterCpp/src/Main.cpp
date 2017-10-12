/**
 * Licensed under MIT license (see LICENSE for details)
 * Copyright (c) 2017 Bartosz Grabias
 */
#include <iostream> /* cout, cin */
#include <iomanip>  /* setfill, setw */
#include <ctime>    /* time */
#include <cstdlib>  /* rand, srand */

#include "StaticArray.h"

/**
 * This program implements O(n) sorting of provided number
 * of randomly generated integers. It achieves this efficiency by
 * using a lot of memory :)
 */

typedef unsigned int number_t;
typedef StaticArray<number_t> array_t;
typedef StaticArray<number_t> bucket_array_t;

struct range_t
{
	const number_t start;
	const number_t end;
	const number_t range;

	range_t(number_t _start, number_t _end)
		: start( min(_start, _end) )
		, end( max(_start, _end) )
		, range( end - start + 1 )
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

number_t random(const range_t& range);
void populate_array(array_t& array, const range_t& range);
void setup_buckets(bucket_array_t& buckets);
array_t sort_array(const array_t& arrayToSort, const range_t& range);
void generate_sort_and_print_numbers(size_t count, const range_t& range);

int main(int argc, char *argv[])
{
	using std::cout;
	using std::cin;
	using std::endl;

	size_t count = 0;
	number_t start = 0, end = 0;

	cout << "Hello! I'll generate and sort numbers for you" << endl;
	cout << "How many numbers should I generate? ";
	cin >> count;
	cout << "What should be the lowest possible number? ";
	cin >> start;
	cout << "What should be the highest possible number? ";
	cin >> end;

	// range_t automatically swaps start and end if start > end
	generate_sort_and_print_numbers(count, range_t(start, end));

	cout << endl << "Press return key to terminate." << endl;
	cin.get(); // Pull last enter key
	cin.get(); // Wait for enter
	return 0;
}

void generate_sort_and_print_numbers(size_t count, const range_t& range)
{
	using std::cout;
	using std::endl;
	using std::setw;

	array_t values(count);
	populate_array(values, range);
	auto sorted = sort_array(values, range);

	cout << std::setfill(' ');

	cout << "       UNSORTED | SORTED" << endl << endl;

	for (size_t i = 0; i < sorted.Size(); i++)
	{
		cout << setw(15) << values[i] << " | "
			<< setw(0) << sorted[i] << '\n';
	}

	cout << endl; // Flush cout to the screen
}

number_t random(const range_t& range)
{
	number_t value = 0;
	number_t accumulator = 0;

	while (accumulator < range.range)
	{
		value += rand();
		accumulator += RAND_MAX;
	}

	return range.start + (value % range.range);
}

void populate_array(array_t& array, const range_t& range)
{
	srand(time(NULL));

	for (size_t i = 0; i < array.Size(); i++)
		array[i] = random(range);
}

void setup_buckets(bucket_array_t& buckets)
{
	for (size_t i = 0; i < buckets.Size(); i++)
		buckets[i] = 0;
}

array_t sort_array(const array_t& arrayToSort, const range_t& range)
{
	bucket_array_t buckets(range.range);
	array_t returnValues(arrayToSort.Size());
	size_t index = 0;

	setup_buckets(buckets);

	for (size_t i = 0; i < arrayToSort.Size(); i++)
	{
		buckets[arrayToSort[i] - range.start]++;
	}

	for (size_t i = 0; i < buckets.Size(); i++)
	{
		for (size_t j = 0; j < buckets[i]; j++)
		{
			returnValues[index++] = range.start + i;
		}
	}

	return returnValues;
}


