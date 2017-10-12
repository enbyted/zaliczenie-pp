#pragma once
/**
* Licensed under MIT license (see LICENSE for details)
* Copyright (c) 2017 Bartosz Grabias
*/

template<typename T> class Bucket
{
public:
	typedef T DataType;
private:
	DataType m_value;
	size_t m_count;
public:
	Bucket()
		: Bucket(0)
	{}

	Bucket(DataType value)
		: m_value(value)
		, m_count(0)
	{}

	size_t Count() const { return m_count; }
	void AddElement() { m_count++; }
};