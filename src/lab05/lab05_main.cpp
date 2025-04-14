#include <array_list_utility.h>
#include <fstream>
#include <chrono>
#include <random>

std::chrono::steady_clock::time_point start, end;

int main(int args, char** argv)
{
	std::random_device device;
	std::uniform_real_distribution<float> distribution(-1000.0f, 1000.0f);
	std::mt19937 generator(device());

	//std::ofstream fp("..\\..\\media\\results.csv");
	std::ofstream fp("..\\..\\..\\media\\results.csv");
	fp << "array size, create-time(ns), shuffle-time(ns), copy-time(ns), save-time(ns), quicksort-time(ms), bubblesort-time(ms), binarysearch-time(ms), linearsearch-time(ms)\n";

	for (int sample_size = 1000; sample_size < 1000000; sample_size += 5000) // eventually go all the way to 1000000
	{
		fp << sample_size << ", ";
		//CREATE
		start = std::chrono::steady_clock::now();
		ssuds::ArrayList<float> flist;
		for (int i = 0; i <= sample_size; i++)
		{
			flist.append(distribution(generator)); 
		}
		end = std::chrono::steady_clock::now();
		std::chrono::nanoseconds elapsed;
		elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
		unsigned long int time_create = elapsed.count();
		fp << time_create << ",  ";

		//SHUFFLE
		start = std::chrono::steady_clock::now();
		ssuds::shuffle(flist, false);
		end = std::chrono::steady_clock::now();
		//std::chrono::nanoseconds elapsed;
		elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
		unsigned long int time_shuffle = elapsed.count();
		fp << time_shuffle << ",  ";

		//COPY
		start = std::chrono::steady_clock::now();
		ssuds::ArrayList<float> flist2(flist);
		end = std::chrono::steady_clock::now();
		//std::chrono::nanoseconds elapsed;
		elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
		unsigned long int time_copy = elapsed.count();
		fp << time_copy << ",  ";

		//SAVE 1000 VALUES
		start = std::chrono::steady_clock::now();
		ssuds::ArrayList<float> savedValues;
		for (int i = 0; i <= 1000; i++)
		{
			savedValues.append(flist[i]);
		}
		end = std::chrono::steady_clock::now();
		//std::chrono::nanoseconds elapsed;
		elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
		unsigned long int time_save = elapsed.count();
		fp << time_save << ",  ";

		//QUICKSORT
		start = std::chrono::steady_clock::now();
		int num_swaps = ssuds::quick_sort(flist, 0, sample_size, ssuds::sort_order::ASCENDING);
		end = std::chrono::steady_clock::now();
		std::chrono::milliseconds elapsedm;
		elapsedm = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
		unsigned long int time_quicksort = elapsedm.count();
		fp << time_quicksort << ",  ";

		//BUBBLESORT
		if (sample_size <= 300000)
		{
			start = std::chrono::steady_clock::now();
			ssuds::bubble_sort(flist2, ssuds::sort_order::ASCENDING);
			end = std::chrono::steady_clock::now();
			//std::chrono::milliseconds elapsed;
			elapsedm = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
			unsigned long int time_bubblesort = elapsedm.count();
			fp << time_bubblesort << ",  ";
		}
		else
		{
			fp << "N/A" << ",  ";
		}

		//BINARY SEARCH
		start = std::chrono::steady_clock::now();
		for (float value : savedValues)
		{
			int index = ssuds::binary_search(flist, value, ssuds::sort_order::ASCENDING);
		}
		end = std::chrono::steady_clock::now();
		//std::chrono::milliseconds elapsed;
		elapsedm = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
		unsigned long int time_binarys = elapsedm.count();
		fp << time_binarys << ",  ";

		//LINEAR SEARCH (FIND)
		start = std::chrono::steady_clock::now();
		for (float value : savedValues)
		{
			flist.find(value);
		}
		end = std::chrono::steady_clock::now();
		//std::chrono::milliseconds elapsed;
		elapsedm = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
		unsigned long int time_linears = elapsedm.count();
		fp << time_linears << ",  ";

		fp << "\n";

	}

	fp.close();
}