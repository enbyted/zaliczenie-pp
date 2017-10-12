/**
 * Licensed under MIT license (see LICENSE for details)
 * Copyright (c) 2017 Bartosz Grabias
 */
using System;

namespace SorterCS
{
	class Program
	{
		static void Main(string[] args)
		{
			uint count, start, end;
			Sorter sorter;
			
			Console.WriteLine("Hello! I'll generate and sort numbers for you");
			Console.Write("How many numbers should I generate? ");
			count = UInt32.Parse(Console.ReadLine());
			Console.Write("What should be the lowest possible number? ");
			start = UInt32.Parse(Console.ReadLine());
			Console.Write("What should be the highest possible number? ");
			end = UInt32.Parse(Console.ReadLine());

			if(start > end)
			{
				uint temp = start;
				start = end;
				end = temp;
			}

			sorter = new Sorter(count, start, end);
			sorter.generateSortAndPrintNumbers();

			Console.WriteLine("Press return key to terminate.");
			Console.ReadLine();
		}
	}
}
