#pragma once
#include <array_list.h>
#include <random>


namespace ssuds
{
	enum class sort_order { ASCENDING,DESCENDING };

	template <typename T>
	void bubble_sort(ArrayList<T>& my_list, sort_order order) // sorts in ascending order
	{
		int n = my_list.size();			// number of elements
		bool is_sorted;
									// We need to do at most n passes to sort
		if (order == sort_order::ASCENDING)
		{
			for (int i = 0; i < n - 1; i++)
			{							// Start of a pass
				is_sorted = true;
				for (int j = 0; j < n - 1; j++)
				{						// Check for out - of - place neighbors
					if (my_list[j] > my_list[j + 1])
					{
						T temp = my_list[j];
						my_list[j] = my_list[j + 1];
						my_list[j + 1] = temp;
						is_sorted = false;
					}
				}
				if (is_sorted == true)
				{
					break;
				}
			}
		}
		else if (order == sort_order::DESCENDING)
		{
			for (int i = 0; i < n - 1; i++)
			{							// Start of a pass
				is_sorted = true;
				for (int j = 0; j < n - 1; j++)
				{						// Check for out - of - place neighbors
					if (my_list[j] < my_list[j + 1])
					{
						T temp = my_list[j];
						my_list[j] = my_list[j + 1];
						my_list[j + 1] = temp;
						is_sorted = false;
					}
				}
				if (is_sorted == true)
				{
					break;
				}
			}
		}
	}

	template <typename T>
	void shuffle(ArrayList<T>& my_list, bool derrangement)
	{
		std::random_device device;
		int n = my_list.size();
		for (int i = n - 1; i > 0; i--)
		{
			int j = 0;
			if (derrangement == false)
			{
				std::uniform_int_distribution<int> distribution(0, i);
				std::mt19937 generator(device());
				j = distribution(generator);
			}
			else
			{
				std::uniform_int_distribution<int> distribution(0, (i - 1));
				std::mt19937 generator(device());
				j = distribution(generator);
			}
			T temp = my_list[j];
			my_list[j] = my_list[i];
			my_list[i] = temp;
		}
	}

	template <typename T>
	int binary_search(ArrayList<T>& my_list, T value, sort_order order)
	{
		if (order == sort_order::ASCENDING)	//the list is in ascending order
		{
			int left = 0;
			int right = my_list.size() - 1;
			while (left <= right)
			{
				int mid = (left + right) / 2;	//halfway between left and right
				if (my_list[mid] == value)
				{
					return mid;
				}
				else if (my_list[mid] > value)
				{
					right = mid - 1;
				}
				else if (my_list[mid] < value)
				{
					left = mid + 1;
				}
			}
			return -1;		//Value Not found
		}
		else if (order == sort_order::DESCENDING)	//the list is in descending order
		{
			int left = 0;
			int right = my_list.size() - 1;
			while (left <= right)
			{
				int mid = (left + right) / 2;
				if (my_list[mid] == value)
				{
					return mid;
				}
				else if (my_list[mid] < value)
				{
					right = mid - 1;
				}
				else if (my_list[mid] > value)
				{
					left = mid + 1;
				}
			}
			return -1;		//Value Not found
		}
		else
			throw std::runtime_error("List must be in ascending or descending order");
	}

	template <typename T>
	void swap(T& a, T& b)
	{
		T temp = a;
		a = b;
		b = temp;
	}

	template <typename T>
	std::pair<int,int> partition(ArrayList<T>& my_list, int left_index, int right_index)
	{ //ASCENDING
		// Get index of pivot
		int mid_index = (left_index + right_index) / 2;
		T pivot_value = my_list[mid_index];
		// Swap last element with pivot
		swap<T>(my_list[mid_index], my_list[right_index]);
		int num_swap = 1;
		// Put elements on "right" side of pivot
		int swap_index = left_index;
		for (int i = left_index; i <= right_index; i++)
		{
			// Note : python range stops before 2nd arg.
			if (my_list[i] <= pivot_value)//my_list[i] is the pivot or should go to its left (changes for descending)
			{
				swap<T>(my_list[i], my_list[swap_index]);
				num_swap++;
				swap_index += 1;
				// Return index of pivot value
				//return swap_index - 1;
			}
		}
		return std::make_pair(swap_index - 1, num_swap);
	}
		
	template <typename T>
	int quick_sort(ArrayList<T>& my_list, int left_index, int right_index, sort_order order)
	{
		int num_swap = 0;
		if (left_index >= right_index)
		{
			// Just one element to sort -- nothing to do!
			return num_swap;
		}

		std::pair temp = std::make_pair(0,0);
		temp = partition<T>(my_list, left_index, right_index);
		int pivot_index = temp.first;
		num_swap += temp.second;
		// pivot is in proper place.Sort halves on either side
		num_swap += quick_sort<T>(my_list, left_index, pivot_index - 1, ssuds::sort_order::ASCENDING);
		num_swap += quick_sort<T>(my_list, pivot_index + 1, right_index, ssuds::sort_order::ASCENDING);
	} 


	// quick_sort function

	// google tests for quick sort

	//main program that tests how long they take to run

	//compare runtimes on excel graph
}