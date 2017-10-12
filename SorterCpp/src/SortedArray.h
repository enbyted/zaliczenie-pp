#pragma once
/**
* Licensed under MIT license (see LICENSE for details)
* Copyright (c) 2017 Bartosz Grabias
*/
#include "Pointers.h"

/**
 * I'm prohibited from using STL so this is 
 * a simplistic implementation of a sorted array
 */
class SortedArray
{
public:
	typedef int DataType;
private:
	int m_capacity;
	int m_size;
	UniquePointer<DataType[]> m_data;
public:
	SortedArray(int initialCapacity = 0);

	int Size() const noexcept { return m_size; }
	int Capacity() const noexcept { return m_capacity; }

	DataType operator[](int index) const;
	void Insert(DataType value);

	// Copy constructor  and assignment won't be needed in this program
	SortedArray(const SortedArray& other) = delete;
	SortedArray& operator=(const SortedArray& other) = delete;
private:
	void Resize(int newCapacity);
};
