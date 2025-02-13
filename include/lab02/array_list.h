#pragma once

#include <iostream>

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
		//ArrayList(unsigned int size_of_T)
		//{
		//	my_array_capacity = 5;
		//	my_array_ptr = new T[my_array_capacity * size_of_T];
		//	my_array_size = 0;
		//
		//}

		/*
		//LAB 3 CONSTRUCTOR
		ArrayList(const std::initializer_list<T>& starting_values)
		{
			//first: initialize the attributes

			//second: iterate throught starting_values and add each to ourself. Complication: the only way to access the values is through initializer_list's iterator.
			// you can use starting_values.size() method

			for (T& cur_value : starting_value)
			{
				//add cur_value to our array
			}
		}

		//COPY CONSTRUCTOR
		ArrayList(const ArrayList& other)
		{
			//makes a deep copy, similar to the = operator 
		}
		*/

		/// <summary>
		/// This is the destructor.
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
		/// //////////////////////////////////////////////// NOT DONE YET /////////////////////////////////////////////////////////////////////////////////////////////////
		void output(std::ostream& os)
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
		/*
		friend std::ostream& operator<<(std::ostream& os, const ArrayList& A) //similar to output function for the iterator
		{
			//make this a friend function outside of the class -- method 3 on whiteboard
			//(use this function the same way as output function)
			A.output(os);
			return os;
		}

		T& operator[](unsigned int index)
		{
			return my_array_ptr[index]
		}

		ArrayList& operator=(const ArrayList& other)
		{
			//throw out any current data and make a deep copy of 'other'
			return *this;
		}

		*/


		/*
		AlIterator begin()
		{
			// (this) is a pointer to the instance of ArrayList that the method is called for
			AlIterator temp(this, 0);
			return temp;
		}

		AlIterator end()
		{
			//end() uses the default constructor, which sets my_list_ptr to null. This will be the flag to say we have reached the end of the array
			AlIterator temp();
			return temp;
		}
		*/



		/*
		class AlIterator
		{
		protected:
			//ATTRIBUTES
			//never make a copy of any data
			//a reference to the array list OR a pointer to the array list

			ArrayList* my_list_ptr;		//my_list
			int my_index;				//my position

		public:

			AlIterator()
			{
				my_list_ptr = null;
				my_index = 0;
			}

			AlIterator(ArrayList* ptr, int starting_index)
			{
				my_list_ptr = ptr;
				my_index = starting_index;
			}

			T& operator*()
			{
				//get it and return it
			}

			AlIterator operator++()
			{
				//move to the next value in the array or, if at the end of the array, return the null-like value
				//return a copy of our self
				my_index++;

				//can check my_list_ptr->size() to find if you are off the end of the array
			}

			AlIterator& operator=(const AlIterator& other)
			{
				//if you do not make an assignment operator, a default one will be created for you
				//the default assignment operator will just copy all the attributes
				return *this; //???
			}

			bool operator!=(const AlIterator& other)
			{
				//determine if it is equal or not
			}

		}
		*/
	};
};
