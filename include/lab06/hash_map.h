#pragma once

#include <iostream>

namespace ssuds
{

	// DONE:			 Total Points: 100
	// a. (10 points) General structure1 and attributes.
	// b. (10 points) Constructor / Destructor
	// c. (15 points) ostream operator
	// d. (10 points) [] operator (I want this to be the only means of adding as well as getting)
	// e. (10 points) contains / find
	// f. (10 points) remove
	// g. (10 points) unit tests(in the unit_tests project)
	// h. (15 points) iterator
	// i. (10 points) good Documentation

	enum class MAPIteratorDirection { FORWARD, BACKWARD };

	template <class K, class V>
	class Map
	{
		// K = Key, V = Value
	protected:

		std::pair<K, V>** my_table;
		unsigned int my_capacity;
		unsigned int my_size;

	public:
		/// <summary>
		/// This is the constructor, it takes no arguments
		/// </summary> 
		Map()
		{
			my_capacity = 10;
			my_table = new std::pair<K, V>* [my_capacity];
			for (unsigned int i = 0; i < my_capacity; i++)
			{
				my_table[i] = nullptr;
			}
		}

		/// <summary>
		/// This is the destructor, it frees up the space allocated for the array used for the table.
		/// </summary>
		~Map()
		{
			delete[] my_table;
		}

		/// <summary>
		/// This method gets the number of objects in the map that have actual values (are not null).
		/// </summary>
		/// <returns> an unsigned integer </returns>
		unsigned int size()
		{
			return my_size;
		}

		/// <summary>
		/// This method gets the number of objects that the map is currently capable of holding.
		/// </summary>
		/// <returns> an unsigned integer </returns>
		unsigned int capacity()
		{
			return my_capacity;
		}

		/// <summary>
		/// This method douples the capacity of the map, re-allocates the array, and puts also the values into the correct positions.
		/// </summary>
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

		/// <summary>
		/// This method returns the value associated with a given key or, if the key is not already in the map, creates a new entry with the given key. If the size of the table reaches 70% capacity,
		/// it calls the grow method.
		/// </summary>
		/// <param name="key"></param>
		/// <returns> a reference to a value of type V</returns>
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

		/// <summary>
		/// This method removes the entry in the map that is associated with a given key.
		/// </summary>
		/// <param name="key"></param>
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

		/// <summary>
		/// This method returns true if there is an entry in the map with the given key, and returns false if an entry with the given key does not exist.
		/// </summary>
		/// <param name="key"></param>
		/// <returns> a boolean </returns>
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

		/// <summary>
		/// This method prints all of the entries in the map with a key/value pair to the given stream as a string.
		/// </summary>
		/// <param name="os"></param>
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

		/// <summary>
		/// This is an overload method for the << operator. It prints all the entries in the map with a key/value pair as a string.
		/// </summary>
		/// <param name="os"></param>
		/// <param name="A"></param>
		/// <returns></returns>
		friend std::ostream& operator<<(std::ostream& os, const Map& A)
		{
			A.output(os);
			return os;
		}

		// ----------------------------------------------------------------------- ITERATOR SUBCLASS -------------------------------------------------------------------------------------------------------

		friend class MAPIterator;

		class MAPIterator
		{
		protected:
			//Map* my_map;
			//int my_index;
			//MAPIteratorDirection my_type;

		public:
			Map* my_map;
			int my_index;
			MAPIteratorDirection my_type;

			/// <summary>
			/// This is the default constructor. It sets all the attributes to default values.
			/// </summary>
			MAPIterator()
			{
				my_map = nullptr;
				my_index = 0;
				my_type = MAPIteratorDirection::FORWARD;
			}

			/// <summary>
			/// This is a constructor that takes arguments for all of the attributes, allowing the attributes to be set when the iterator is made.
			/// </summary>
			/// <param name="map"></param>
			/// <param name="starting_index"></param>
			/// <param name="direction"></param>
			MAPIterator(Map* map, int starting_index, MAPIteratorDirection direction)
			{
				my_map = map;
				my_index = starting_index;
				my_type = direction;
			}

			/// <summary>
			/// This is an overload method for the != operator. It takes a const reference to a MAPIterator object.
			/// It returns true if the attribute my_type or my_index are not the same as the given iterator.
			/// </summary>
			/// <param name="other"></param>
			/// <returns> a boolean </returns>
			bool operator!=(const MAPIterator& other) const
			{
				if ( my_type != other.my_type || my_index != other.my_index)
					return true;

				else
					return false;
			}

			/// <summary>
			/// This is an overload method for the == operator. It takes a const reference to a MAPIterator object.
			/// It returns true if the attribute my_type and my_index are the same as the given iterator.
			/// </summary>
			/// <param name="other"></param>
			/// <returns> a boolean </returns>
			bool operator==(const MAPIterator& other) const
			{
				if (my_type == other.my_type && my_index == other.my_index)
					return true;

				else
					return false;
			}

			/// <summary>
			/// This is an overload method for the *, or dereference, operator. It returns the pair object, with types K and V, that the iterator is currently pointing to.
			/// </summary>
			/// <returns> std::pair object of type K, V </returns>
			std::pair<K, V> operator*()
			{
				std::pair<K, V>* ptr = my_map->my_table[my_index];
				std::pair<K, V> temp = *ptr;
				return temp;
			}

			/// <summary>
			/// This is the overload method for the ++ operator. If it is a forward iterator, it increments my_index. If it is a reverse iterator, it decrements my_index.
			/// </summary>
			void operator++()
			{
				if (my_type == MAPIteratorDirection::FORWARD)
				{
					my_index++;
					if (my_index >= int(my_map->capacity()))
					{
						my_index = -1;
					}
				}
				else //if backwards iterator
				{
					my_index--;
					if (my_index < 0)
					{
						my_index = -1;
					}
				}
			}

		};


		/// <summary>
		/// This is the begin method used for forward iteration. 
		/// It returns an iterator with the attribute my_map set to itself, the attribute my_index set to 0, and the iterator type set to forward.
		/// </summary>
		/// <returns> a MAPIterator object </returns>
		MAPIterator begin()
		{
			MAPIterator temp(this, 0, MAPIteratorDirection::FORWARD);
			return temp;
		}

		/// <summary>
		/// This is the end method used for forward iteration.
		/// It returns an iterator with the attribute my_map set to itself, the attribute my_index set to -1, and the iterator type set to forward.
		/// </summary>
		/// <returns> a MAPIterator object </returns>
		MAPIterator end()
		{
			return MAPIterator (this, -1, MAPIteratorDirection::FORWARD);
		}

		/// <summary>
		/// This is the begin method used for backwards iteration. 
		/// It returns an iterator with the attribute my_map set to itself, the attribute my_index set to one less than the capacity of the map, and the iterator type set to backwards.
		/// </summary>
		/// <returns> a MAPIterator object </returns>
		MAPIterator rbegin()
		{
			MAPIterator temp(this, my_capacity - 1, MAPIteratorDirection::BACKWARD);
			return temp;
		}

		/// <summary>
		/// This is theend method used for backwards iteration. 
		/// It returns an iterator with the attribute my_map set to itself, the attribute my_index set to -1, and the iterator type set to backwards.
		/// </summary>
		/// <returns> a MAPIterator object </returns>
		MAPIterator rend()
		{
			MAPIterator temp(this, -1, MAPIteratorDirection::BACKWARD);
			return temp;
		}

		/// <summary>
		/// This method takes a key of type K, and returns an iterator object pointing to the entry in the map associated with the given key.
		/// If there is no entry associated with the given key, it returns an iterator equal to the end method.
		/// </summary>
		/// <param name="key"></param>
		/// <returns> a MAPIterator object </returns>
		MAPIterator find(K key)
		{
			MAPIterator mit(this, 0, MAPIteratorDirection::FORWARD);
			while (mit != this->end())
			{
				if (mit.my_map->my_table[mit.my_index] != nullptr)
				{
					std::pair<K, V> temp = *mit;
					if (temp.first == key)
						return mit;
				}
				++mit;
			}
			return mit; // this will return end()
		}

	};

}