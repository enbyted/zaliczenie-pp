/**
* Licensed under MIT license (see LICENSE for details)
* Copyright (c) 2017 Bartosz Grabias
*/
#include "BucketSorter.h"

StaticArray<BucketSorter::DataType> BucketSorter::sort(StaticArray<DataType> values, size_t bucketCount)
{
	if (bucketCount == 0) bucketCount = values.Size() + 1;

	// bucket entry index = 0 means no value
	StaticArray<size_t> buckets(bucketCount); // this holds index to bucketEntries
	StaticArray<BucketEntry> bucketEntires(values.Size() + 1);
	DataType bucketWidth = (m_maxVal - m_minVal) / (buckets.Size() - 1);

	// Put each value into apropriate bucket
	for (size_t i = 0; i < values.Size(); i++)
	{
		DataType value = values[i];
		size_t bucketIndex = (size_t)((value - m_minVal) / bucketWidth);
		size_t entryIndex = i + 1;

		bucketEntires[entryIndex].value = value;

		AddEntryToBucket(buckets, bucketEntires, bucketIndex, entryIndex, value);
	}

	// Read buckets and put them into output array
	StaticArray<DataType> output(values.Size());

	size_t index = 0;
	for (size_t i = 0; i < buckets.Size(); i++)
	{
		size_t bucketIndex = buckets[i];
		while (bucketIndex != 0)
		{
			output[index++] = bucketEntires[bucketIndex].value;
			bucketIndex = bucketEntires[bucketIndex].next;
		}
	}

	return output;
}

void BucketSorter::AddEntryToBucket(
	StaticArray<size_t>& buckets, 
	StaticArray<BucketEntry>& bucketEntires, 
	size_t bucketIndex, 
	size_t entryIndex,
	DataType value
) {
	if (buckets[bucketIndex] == 0)
		// Bucket is empty - this is the first value
	{
		buckets[bucketIndex] = entryIndex;
	}
	else
	{
		// Find place to put our value, so the linked list is sorted
		size_t curIndex = buckets[bucketIndex];
		size_t prevIndex = 0;
		while ((curIndex != 0) && (bucketEntires[curIndex].value <= value))
		{
			prevIndex = curIndex;
			curIndex = bucketEntires[curIndex].next;
		}

		if (prevIndex == 0)
			// All values in bucket are greater than us
		{
			bucketEntires[entryIndex].next = curIndex;
			buckets[bucketIndex] = entryIndex;
		}
		else
			// We are somewhere in the middle or in the end (curIndex = 0)
		{
			bucketEntires[prevIndex].next = entryIndex;
			bucketEntires[entryIndex].next = curIndex;
		}
	}
}
