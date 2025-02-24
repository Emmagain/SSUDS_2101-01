#pragma once

#include <iostream>
#include <initializer_list>

namespace ssuds
{

	template <class T>
	class ArrayList
	{
	private:
		T* my_array_ptr;
		unsigned int my_array_size;
		unsigned int my_array_capacity;

	public:

		/// <summary>
		/// This is the default constructor, it takes no arguments
		/// </summary>
		/// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		ArrayList()
		{
			my_array_capacity = 5;
			my_array_ptr = new T[my_array_capacity];
			my_array_size = 0;

		}

		/// <summary>
		/// This a constructor that reserves an amount of space equal to the given unsigned int. This is not correct right now.
		/// </summary>
		/// <param name="size_of_T"></param>
		ArrayList(unsigned int size_of_T)
		{
			my_array_capacity = size_of_T;
			my_array_ptr = nullptr;
			my_array_size = 0;
		}

		/// <summary>
		/// This is the move contructor, which is used when an ArrayList is returned. It makes a shallow copy of the given ArrayList, then nullifies the original pointer.
		/// </summary>
		/// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//MOVE CONTRUSTOR
		ArrayList(ArrayList&& other) //&& means that it is a move constructor
		{
			//steal the identity of other - similar to shallow copy
			my_array_ptr = other->my_array_ptr;
			my_array_size = other->my_array_size;
			my_array_capacity = other->my_array_capacity;
			//now set other to not point to the array anymore. The new pointer is now the only pointer for the array.
			other->my_array_ptr = nullptr;
		}

		/// <summary>
		/// This is the initializer-list constructor.
		/// </summary>
		/// <param name="starting_values"></param>
		ArrayList(const std::initializer_list<T>& init_list)
		{
			// We need to set our attributes to starting values.
			my_array_capacity = 5;
			my_array_ptr = new T[my_array_capacity];
			my_array_size = 0;

			// init_list has size() method and an iterator, but that's it.
			// We could use a manual iterator
			//std::initializer_list<T>::iterator it = init_list.begin();
			for (T cur_val : init_list) //could also use a while loop if you want
			{
				append(cur_val);
			}
		}

		/// <summary>
		/// This is the copy constructor, which creates a deep copy of the given ArrayList object.
		/// </summary>
		//COPY CONSTRUCTOR
		/// ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		ArrayList(const ArrayList& other)
		{
			//makes a deep copy, similar to the = operator 
			my_array_ptr = new T[other.my_array_capacity];
			my_array_size = other.my_array_size;
			for (unsigned int i = 0; i < my_array_size; i++)
			{
				my_array_ptr[i] = other.my_array_ptr[i];
			}
		}

		/// <summary>
		/// This is the destructor, it frees up the space allocated for the array.
		/// </summary>
		/// ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		~ArrayList()
		{
			delete[] my_array_ptr;
		}


		/// <summary>
		/// This method returns the number of objects in the array.
		/// </summary>
		/// <returns></returns>
		/// ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		int size()
		{
			return my_array_size;
		}

		/// <summary>
		/// This method returns the total capacity of the array, or how many items could fit into the array.
		/// </summary>
		/// <returns></returns>
		/// ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		int capacity()
		{
			return my_array_capacity;
		}

		/// <summary>
		/// This method adds an item to the end of the array and grows the array if necessary.
		/// </summary>
		/// <param name="new_value"></param>
		/// ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		void append(const T& new_value)
		{
			// See if that item already exists -- if we raise an exception it'll get us out of this function
			//NOT USING YET
			//for (unsigned int i = 0; i < mArraySize; i++)
			//{
			//	if (mArray[i].get_id() == p.get_id())
			//		throw std::runtime_error("Person with id " + std::to_string(p.get_id()) + " already exists!");
			//}

			// We have data in the array so must copy it to a new larger array (as on the slides)
			// ...make a larger array

			if (my_array_size < my_array_capacity-1)
			{
				//add new value to end of array and increase size of array variable
				my_array_ptr[my_array_size] = new_value;
				my_array_size++;

			}
			else
			{
				my_array_capacity *= 2;
				T* temp_array = new T[my_array_capacity];

				//copy data into new array 
				for (unsigned int i = 0; i < my_array_size; i++)
					temp_array[i] = my_array_ptr[i];

				//free the old array and set pointer to new array
				delete[] my_array_ptr;
				my_array_ptr = temp_array;

				//add new value to end of array and increase size of array variable
				my_array_ptr[my_array_size] = new_value;
				my_array_size++;

			}
		}

		/// <summary>
		/// This method adds an item to the beginning of the array and grows the array if necessary.
		/// </summary>
		/// <param name="new_value"></param>
		/// ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		void prepend(const T & new_value)
		{
			if (my_array_size >= my_array_capacity - 1)
			{
				my_array_capacity *= 2;
				T* temp_array = new T[my_array_capacity];
				for (unsigned int i = 0; i < my_array_size; i++)
					temp_array[i+1] = my_array_ptr[i];
				delete[] my_array_ptr;
				my_array_ptr = temp_array;
			}
			else
			{
				//copy each value into the next index to the right
				for (unsigned int i = my_array_size; i > 0; i--)
					my_array_ptr[i] = my_array_ptr[i-1];
			}
			//add the new value at the index 0, which should now be blank
			my_array_ptr[0] = new_value;
			//increase the size of array variable
			my_array_size++;

		}

		/// <summary>
		/// This methods adds an item to a specified location in the array and grows the array if necessary.
		/// </summary>
		/// <param name="new_value"></param>
		/// ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		void insert(const T& new_value, unsigned int index)
		{
			if (my_array_size >= my_array_capacity-1)
			{
				my_array_capacity *= 2;
				T* temp_array = new T[my_array_capacity];

				//copy data into new array 
				for (unsigned int i = 0; i < my_array_size; i++)
					temp_array[i] = my_array_ptr[i];

				//free the old array and set pointer to new array
				delete[] my_array_ptr;
				my_array_ptr = temp_array;
			}

			//starting at the index, copy each value into the next index to the right
			for (unsigned int i = my_array_size; i > index; i--)
				my_array_ptr[i] = my_array_ptr[i-1];
			//add the new value at the index, which should now be blank
			my_array_ptr[index] = new_value;
			//increase the size of array variable
			my_array_size++;

		}

		/// <summary>
		/// This method returns a reference to the item at a specified location in the array.
		/// </summary>
		/// <param name="index"></param>
		/// <returns></returns>
		/// ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		const T& at(unsigned int index)
		{
			const T& index_ref = my_array_ptr[index];
			return index_ref;
		}

		/// <summary>
		/// This method returns a string? output of a specified item.
		/// </summary>
		/// <param name="os"></param>
		/// <returns></returns>
		/// ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		void output(std::ostream& os) const
		{
			os << "[";
			for (unsigned int i = 0; i < my_array_size; i++)
			{
				os << my_array_ptr[i];
				if (i != my_array_size-1)
					os << ", ";
			}
			
			os << "]";
		}

		/// <summary>
		/// This method removes the item at the specified location in the array from the array, and shrinks the array in necessary.
		/// </summary>
		/// <param name="index"></param>
		/// ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		void remove(unsigned int index)
		{
			//starting with the index immediately after the value we want to remove, copy each value into the next index to the left. 
			// This will overwrite the value we want to remove without leaving a blank value in its place.
			for (unsigned int i = index; i < my_array_size; i++)
				my_array_ptr[i] = my_array_ptr[i+1];
			//decrease the size of array variable
			my_array_size--;

			if (my_array_size <= (0.25 * my_array_capacity))
			{
				my_array_capacity *= 0.5;
				T* temp_array = new T[my_array_capacity];

				for (unsigned int i = 0; i < my_array_size; i++)
					temp_array[i] = my_array_ptr[i];

				delete[] my_array_ptr;
				my_array_ptr = temp_array;
			}
		}

		/// <summary>
		/// This method returns the index of the first item in the array with the specified value.
		/// </summary>
		/// <param name="start_index"></param>
		/// <param name="ref"></param>
		/// <returns></returns>
		/// //////////////////////////////////////////////// NOT DONE YET /////////////////////////////////////////////////////////////////////////////////////////////////
		int find(const T& value_ref, unsigned int start_index=0)
		{
			for (unsigned int i = start_index; i < my_array_size; i++)
			{
				if (my_array_ptr[i] == value_ref)
				{
					return i;
				}
			}

			return -1;
		}

		//|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||| LAB 3 ||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
		
		/// <summary>
		/// This is the overload method for the << operator. It returns an ostream object that can be printed as a string.
		/// </summary>
		/// <param name="os"></param>
		/// <param name="A"></param>
		/// <returns></returns>
		friend std::ostream& operator<<(std::ostream& os, const ArrayList& A) //similar to output function for the iterator
		{
			//make this a friend function outside of the class -- method 3 on whiteboard
			//(use this function the same way as output function)
			A.output(os);
			return os;
		}

		/// <summary>
		/// This is the overload method for the [] operator. It is used to find the item at a specific index in the array.
		/// </summary>
		/// <param name="index"></param>
		/// <returns></returns>
		T& operator[](unsigned int index)
		{
			return my_array_ptr[index];
		}

		/// <summary>
		/// This is the overload method for the = or assignment operator. It deletes any data in the array and makes a deep copy of the given array.
		/// </summary>
		/// <param name="other"></param>
		/// <returns></returns>
		ArrayList& operator=(const ArrayList& other)
		{
			//throw out any current data and make a deep copy of 'other'
			delete[] my_array_ptr;
			my_array_ptr = new T[other->my_array_capacity];
			my_array_size = other->my_array_size;
			for (unsigned int i = 0; i < my_array_size; i++)
			{
				my_array_ptr[i] = other->my_array_ptr[i];
			}

			return *this;
		}


		// ///////////////////////////////////////////////////////// AlITERATOR SUBCLASS ////////////////////////////////////////////////////////////////////////////////////////////////////
		class AlIterator
		{
		protected:
			//ATTRIBUTES
			//never make a copy of any data
			//a reference to the array list OR a pointer to the array list

			ArrayList* my_list_ptr;		//my_list
			int my_index;				//my position
			bool is_reverse;			//tells if the iterator goes through normally or in reverse

		public:

			/// <summary>
			/// This is the default constructor. It sets all the attributes to default values.
			/// </summary>
			AlIterator()
			{
				my_list_ptr = nullptr;
				my_index = 0;
				is_reverse = false;
			}

			/// <summary>
			/// This methods allows you to set is_reverse to true or false.
			/// </summary>
			/// <param name="rev"></param>
			void set_reverse(bool rev)
			{
				is_reverse = rev;
			}

			/// <summary>
			/// This is a constructor that allows the attributes to be set when the Iterator object is constructed.
			/// </summary>
			/// <param name="ptr"></param>
			/// <param name="starting_index"></param>
			/// <param name="if_reverse"></param>
			AlIterator(ArrayList* ptr, int starting_index, bool if_reverse)
			{
				my_list_ptr = ptr;
				my_index = starting_index;
				is_reverse = if_reverse;
			}

			/// <summary>
			/// This is the overload emthod for the * operator. It returns a reference to the item that the iterator is currently pointing to.
			/// </summary>
			/// <returns></returns>
			const T& operator*()
			{
				//get it and return it
				return my_list_ptr->at(my_index);
			}

			/// <summary>
			/// This is the overload method for the ++ operator. It increments the iterator if it is not a reverse iterator, and decrements the iterator if it is a reverse iterator.
			/// </summary>
			/// <returns></returns>
			AlIterator operator++()
			{
				//move to the next value in the array or, if at the end of the array, return the null-like value
				//return a copy of our self
				if (is_reverse == false)
				{
					my_index++;
					if (my_index > my_list_ptr->my_array_size-1)
					{
						my_list_ptr = nullptr;
					}
				}
				else
				{
					my_index--;
					if (my_index < 0)
					{
						my_list_ptr = nullptr;
					}
				}
				return *this;
			}

			/// <summary>
			/// This is the overload method for the + operator. It adds to the iterator if it is not a reverse iterator, and subtracts from the iterator if it is a reverse iterator.
			/// </summary>
			/// <returns></returns>
			AlIterator operator+()
			{
				if (is_reverse == true)
				{
					my_index++;
					if (my_index > my_list_ptr->my_array_size-1)
					{
						my_list_ptr = nullptr;
					}
				}
				else
				{
					my_index--;
					if (my_index > my_list_ptr->my_array_size)
					{
						my_list_ptr = nullptr;
					}
				}
				return *this;
			}

			bool operator!=(const AlIterator& other)
			{
				//determine if it is equal or not
				if (my_list_ptr != other.my_list_ptr || my_index != other.my_index || is_reverse != other.is_reverse)
					return true;
				else
					return false;
			}

		};

		/// <summary>
		/// This is the begin method used for iteration. It points to the first item in the array, so that the array can be iterated through completely.
		/// </summary>
		/// <returns></returns>
		AlIterator begin()
		{
			// (this) is a pointer to the instance of ArrayList that the method is called for
			AlIterator temp(this, 0, false);
			return temp;
		}

		/// <summary>
		/// This is the end method used for iteration. It is used to check when you have passed the last item at the end of the array, so that you can stop iterating.
		/// </summary>
		/// <returns></returns>
		AlIterator end()
		{
			//end() uses the default constructor, which sets my_list_ptr to null. This will be the flag to say we have reached the end of the array
			AlIterator temp(nullptr, my_array_size, false);
			return temp;
		}

		/// <summary>
		/// This is the begin method used for reverse iteration. It points to the last item in the array, so that the array can be iterated through from end to beginning.
		/// </summary>
		/// <returns></returns>
		AlIterator rbegin()
		{
			//set to the end of the array list
			AlIterator temp(this, my_array_size-1, true);
			return temp;
		}

		/// <summary>
		/// This is the end method for reverse iteration. It is used to check when you reach the first item in the array.
		/// </summary>
		/// <returns></returns>
		AlIterator rend()
		{
			AlIterator temp(nullptr, -1, true);
			return temp;
		}
		
	};
};
