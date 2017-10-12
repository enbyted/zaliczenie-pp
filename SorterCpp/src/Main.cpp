/**
 * Licensed under MIT license (see LICENSE for details)
 * Copyright (c) 2017 Bartosz Grabias
 */
#include <iostream> /* cout, cin */
#include <iomanip>  /* setfill, setw */
#include <ctime>    /* time */
#include <cstdlib>  /* rand, srand */

#include "Bucket.h"
#include "StaticArray.h"

/**
 * This program implements O(n)** sorting of provided number
 * of randomly generated integers. It achieves this efficiency by
 * using a lot of memory :)
 */

typedef unsigned int number_t;
typedef StaticArray<number_t> array_t;
typedef Bucket<number_t> bucket_t;
typedef StaticArray<bucket_t> bucket_array_t;

number_t my_rand(number_t range)
{
	number_t value = 0;
	number_t accumulator = 0;

	while (accumulator < range)
	{
		value += rand();
		accumulator += RAND_MAX;
	}

	return value % range;
}

void populate_array(array_t& array, number_t start, number_t end)
{
	number_t range = end - start + 1;
	srand(time(NULL));

	for (size_t i = array.Size(); i < array.Capacity(); i++)
	{
		array.PushBack(start + my_rand(range));
	}
}

bucket_array_t setup_buckets(number_t count, number_t start)
{
	bucket_array_t buckets(count);
	for (number_t i = 0; i < count; i++)
	{
		buckets.EmplaceBack(start + i);
	}
	return buckets;
}

array_t sort_array(const array_t& arrayToSort, number_t start, number_t end)
{
	number_t range = end - start + 1;
	bucket_array_t buckets = setup_buckets(range, start);
	array_t returnValues(arrayToSort.Size());

	for (size_t i = 0; i < arrayToSort.Size(); i++)
	{
		buckets[arrayToSort[i] - start].AddElement();
	}

	for (size_t i = 0; i < buckets.Size(); i++)
	{
		for (size_t j = 0; j < buckets[i].Count(); j++)
		{
			returnValues.PushBack(start + i);
		}
	}

	return returnValues;
}

void generate_sort_and_print_numbers(size_t count, size_t start, size_t end)
{
	using std::cout;
	using std::endl;
	using std::setw;

	array_t values(count);
	populate_array(values, start, end);
	auto sorted = sort_array(values, start, end);

	cout << std::setfill(' ');

	cout << "       UNSORTED | SORTED" << endl << endl;

	for (size_t i = 0; i < sorted.Size(); i++)
	{
		cout << setw(15) << values[i] << " | " 
			 << setw(0) << sorted[i] << '\n';
	}

	cout << endl; // Flush the buffer
}

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

	if (end < start)
	{
		number_t temp = end;
		end = start;
		start = temp;
	}

	generate_sort_and_print_numbers(count, start, end);
	cout << endl << "Press return key to terminate." << endl;
	cin.get(); // Pull last enter key
	cin.get(); // Wait for enter
	return 0;
}