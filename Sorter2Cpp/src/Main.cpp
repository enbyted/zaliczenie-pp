/**
 * Licensed under MIT license (see LICENSE for details)
 * Copyright (c) 2017 Bartosz Grabias
 */
#include <iostream> /* cout, cin */
#include <iomanip>  /* setfill, setw */
#include <ctime>    /* time */
#include <cstdlib>  /* rand, srand */

#include "StaticArray.h"
#include "BucketSorter.h"
#include "Helper.h"

number_t random(const range_t& range);
void populate_array(array_t& array, const range_t& range);
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

template<typename T> StaticArray<number_t> sort_numbers(size_t count, const range_t& range, StaticArray<number_t>& values)
{
	BucketSorter sorter(range.start, range.end);
	return sorter.sort(values);
}

template<> StaticArray<number_t> sort_numbers<unsigned int>(size_t count, const range_t& range, StaticArray<number_t>& values)
{
	BucketSorter sorter(range.start, range.end);
	return sorter.sort(values, range.range);
}

void generate_sort_and_print_numbers(size_t count, const range_t& range)
{
	using std::cout;
	using std::endl;
	using std::setw;

	array_t values(count);
	populate_array(values, range);
	auto sorted = sort_numbers<number_t>(count, range, values);

	cout << std::setfill(' ');

	cout << "       UNSORTED | SORTED" << endl << endl;

	for (size_t i = 0; i < sorted.Size(); i++)
	{
		cout << setw(15) << values[i] << " | "
			<< setw(0) << sorted[i] << '\n';
	}

	cout << endl; // Flush cout to the screen
}

void populate_array(array_t& array, const range_t& range)
{
	srand(time(NULL));

	for (size_t i = 0; i < array.Size(); i++)
		array[i] = random<number_t>(range);
}



