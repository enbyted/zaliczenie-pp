/**
* Licensed under MIT license (see LICENSE for details)
* Copyright (c) 2017 Bartosz Grabias
*/
#include "SortedArray.h"
#include "Exceptions.h"

SortedArray::SortedArray(int initialCapacity)
{
	if(initialCapacity > 0)
		Resize(initialCapacity);
}

SortedArray::DataType SortedArray::operator[](int index) const
{
	if (index < 0 || index >= m_size)
		throw ArgumentOutOfRange("Podany indeks jest poza granicami.");

	return m_data[index];
}

void SortedArray::Insert(DataType value)
{
	if (m_capacity <= m_size)
		Resize(m_size * 2);

	if (m_data[m_size - 1] <= value)
	{
		m_data[m_size++] = value;
	}
	else 
	{
		// Find first index that contains value less than or equal to provided
		int index = m_size - 1;
		for (; index >= 0; index--)
			if (m_data[index] <= value) break;

		// move everything after this index forward by one
		for (int i = m_size - 1; i > index; i++)
		{

		}
	}
}

void SortedArray::Resize(int newCapacity)
{
	UniquePointer<DataType[]> newData = new DataType[newCapacity];
	
	// Copy original data
	for (int i = 0; i < m_size; i++)
		newData[i] = m_data[i];

	m_data.swap(newData);
	m_capacity = newCapacity;
}
