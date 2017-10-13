#pragma once
/**
* Licensed under MIT license (see LICENSE for details)
* Copyright (c) 2017 Bartosz Grabias
*/

#include "StaticArray.h"
#include "Helper.h"

class BucketSorter
{
public:
	//typedef unsigned int DataType;
	typedef number_t DataType;
private:
	struct BucketEntry
	{
		DataType value = 0;
		size_t next = 0;
	};
	DataType m_minVal;
	DataType m_maxVal;

public:
	BucketSorter(DataType min, DataType max)
		: m_minVal(min)
		, m_maxVal(max)
	{}

	StaticArray<DataType> sort(StaticArray<DataType> values, size_t buckets = 0);

private:
	void AddEntryToBucket(
		StaticArray<size_t>& buckets, 
		StaticArray<BucketEntry>& bucketEntires,
		size_t bucketIndex,
		size_t entryIndex,
		DataType value);
};