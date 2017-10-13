#pragma once
/**
* Licensed under MIT license (see LICENSE for details)
* Copyright (c) 2017 Bartosz Grabias
*/

class IndexOutOfBounds {};

/**
 * Array with constant size
 */
template<typename T> class StaticArray
{
public:
	typedef T DataType;
private:
	DataType* m_data;
	size_t m_size;
public:
	StaticArray(size_t size)
		: m_data(new DataType[size]())
		, m_size(size)
	{}

	StaticArray(const StaticArray& other)
		: m_data(new DataType[other.m_size])
		, m_size(other.m_size)
	{
		for (size_t i = 0; i < m_size; i++)
			m_data[i] = other.m_data[i];
	}

	StaticArray& operator= (const StaticArray& other) = delete;

	~StaticArray() noexcept
	{
		if(m_data)
			delete[] m_data;
		m_data = nullptr;
	}

	size_t Size() const { return m_size; }

	DataType& operator[](size_t index)
	{
		if (index >= Size())
			throw IndexOutOfBounds();

		return m_data[index];
	}

	const DataType& operator[](size_t index) const
	{
		if (index >= Size())
			throw IndexOutOfBounds();

		return m_data[index];
	}
};