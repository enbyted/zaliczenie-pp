#pragma once
/**
* Licensed under MIT license (see LICENSE for details)
* Copyright (c) 2017 Bartosz Grabias
*/

class ArrayFull {};
class IndexOutOfBounds {};

/**
 * Array with constant maximum capacity
 */
template<typename T> class StaticArray
{
public:
	typedef T DataType;
private:
	struct ControlBlock
	{
		size_t capacity;
		size_t size;
		size_t refCount;
	};

	DataType* m_data;
	ControlBlock* m_controlBlock;
public:
	StaticArray(size_t capacity)
		: m_data(new DataType[capacity])
		, m_controlBlock(new ControlBlock{capacity, 0, 1})
	{}

	StaticArray(const StaticArray& other)
		: m_data(other.m_data)
		, m_controlBlock(other.m_controlBlock)
	{
		m_controlBlock->refCount++;
	}

	~StaticArray() noexcept
	{
		if (!m_controlBlock) return;

		if(m_controlBlock->refCount)
			m_controlBlock->refCount--;

		if (m_controlBlock->refCount == 0)
		{
			if(m_data)
				delete[] m_data;
			delete m_controlBlock;
		}

		m_data = nullptr;
		m_controlBlock = nullptr;
	}

	size_t Size() const { return m_controlBlock->size; }
	size_t Capacity() const { return m_controlBlock->capacity; }

	void PushBack(DataType element)
	{
		if (Size() == Capacity())
			throw ArrayFull();
			
		m_data[m_controlBlock->size++] = element;
	}

	template<typename ...Types> void EmplaceBack(Types ... args)
	{
		if (Size() == Capacity())
			throw ArrayFull();

		new(&m_data[m_controlBlock->size++]) T(args...);
	}

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