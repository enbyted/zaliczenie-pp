/**
 * Licensed under MIT license (see LICENSE for details)
 * Copyright (c) 2017 Bartosz Grabias
 */
using System;

namespace SorterCS
{
	class Sorter
	{
		private uint count, start, range;
		private uint[] buckets;
		private uint[] unsorted, sorted;

		public Sorter(uint count, uint start, uint end)
		{
			this.count = count;
			this.start = start;

			range = end - start + 1;

			buckets = new uint[range];
			unsorted = new uint[count];
			sorted = new uint[count];
		}

		public void generateSortAndPrintNumbers()
		{
			generateNumbers();
			sort();

			Console.WriteLine("       UNSORTED | SORTED");

			for(uint i = 0; i < count; i++)
			{
				Console.WriteLine("{0, 15} | {1}", unsorted[i], sorted[i]);
			}
			Console.WriteLine();
		}

		private void generateNumbers()
		{
			Random r = new Random();
			for (int i = 0; i < count; i++)
			{
				// Fix for values > 2G
				// R.next() returns a 31 bit random value
				uint randomL = (uint)(r.Next());
				uint randomH = (uint)(r.Next());
				// Adding two of them gives 32 bits 
				unsorted[i] = start + (randomL + randomH) % range;
			}
		}

		private void sort()
		{
			// Fill buckets
			for (int i = 0; i < count; i++)
			{
				buckets[unsorted[i] - start]++;
			}

			// Fill output array
			uint idx = 0;
			for (uint i = 0; i < buckets.Length; i++)
			{
				for(uint j = 0; j < buckets[i]; j++)
				{
					sorted[idx++] = i + start;
				}
			}
		}
	}
}
