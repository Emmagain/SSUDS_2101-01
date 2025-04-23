#pragma once

#include <iostream>

namespace ssuds
{
	// ASK IN CLASS:
	// 

	// TO DO:
	// h. (15 points) iterator
	// i. (10 points) good Documentation

	// IN PROGRESS:
	// g. (10 points) unit tests(in the unit_tests project)
	// e. (10 points) contains / find		(Done: contains || To Do: find)

	// DONE:			 Total Points: 45
	// a. (10 points) General structure1 and attributes.
	// b. (10 points) Constructor / Destructor
	// c. (15 points) ostream operator
	// d. (10 points) [] operator (I want this to be the only means of adding as well as getting)
	// f. (10 points) remove

	template <class K, class V>
	class Map
	{
		// K = Key, V = Value
	protected:

		std::pair<K, V>** my_table;
		unsigned int my_capacity;
		unsigned int my_size;

	public:

		Map()
		{
			my_capacity = 10;
			my_table = new std::pair<K, V>* [my_capacity];
			for (unsigned int i = 0; i < my_capacity; i++)
			{
				my_table[i] = nullptr;
			}
		}

		~Map()
		{
			delete[] my_table;
		}

		unsigned int size()
		{
			return my_size;
		}

		unsigned int capacity()
		{
			return my_capacity;
		}

		void grow()
		{
			unsigned int cur_size = my_size;
			unsigned int old_capacity = my_capacity;
			my_capacity = my_capacity * 2;

			std::pair<K, V>** new_table = new std::pair<K, V>*[my_capacity];
			for (unsigned int i = 0; i < my_capacity; i++)
			{
				new_table[i] = nullptr;
			}
			// ADD ALL THE PREVIOUS VALUES TO NEW TABLE
			std::pair<K, V>** old_table = my_table;
			my_table = new_table;
			for (unsigned int i = 0; i < old_capacity; i++)
			{
				if (old_table[i] != nullptr)
				{ 
					(*this)[old_table[i]->first] = old_table[i]->second;
				}
			}
			my_size = cur_size;
			// DELETE my_table
			delete[] old_table;
		}

		V& operator[](K key)
		{
			if (my_size >= my_capacity * 0.7)
			{
				this->grow();
			}
			// ADD NEW VALUE
			std::hash<K> hash;
			unsigned int place = hash(key) % my_capacity;
			for (unsigned int i = place; i < my_capacity; )
			{
				if (my_table[i] == nullptr)
				{
					my_table[i] = new std::pair<K, V>;
					my_table[i]->first = key;
					my_size++;
					//V& result = my_table[i].second();
					return my_table[i]->second;//result;
				}
				else if (my_table[i]->first == key)
				{
					return my_table[i]->second;
				}
				i++;
				if (i >= my_capacity-1)
				{
					i = 0;
				}
			}
		}

		void remove(K& key)
		{
			std::hash<K> hash;
			unsigned int place = hash(key) % my_capacity;
			bool done = false;
			for (unsigned int i = place; i < my_capacity; )
			{
				if (my_table[i] == nullptr)
				{
					int wc;
				}
				else if (my_table[i]->first == key)
				{
					my_table[i] = nullptr;
					my_size--;
				}
				i++;
				if (i >= my_capacity - 1)
				{
					if (done == false)
					{
						i = 0;
						done = true;
					}
					break;
				}
			}
		}

		bool contains(K& key)
		{
			for (unsigned int i = 0; i < my_capacity; )
			{
				if (my_table[i] == nullptr)
					i++;
				else if (my_table[i]->first == key)
					return true;
				else
					i++;
			}
			return false;
		}

		void output(std::ostream& os) const
		{
			os << "{";
			unsigned int s = 0;
			unsigned int i = 0;
			for (i = 0; i < my_capacity; i++)
			{
				if (my_table[i] != nullptr)
				{
					os << my_table[i]->first;
					os << ":";
					os << my_table[i]->second;
					if (s < my_size - 1)
					{
						os << ", ";
					}
					s++;
				}
			}
			os << "}";
		}

		friend std::ostream& operator<<(std::ostream& os, const Map& A)
		{
			A.output(os);
			return os;
		}


	};

}