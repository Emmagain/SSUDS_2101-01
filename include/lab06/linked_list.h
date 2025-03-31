#pragma once

#include <iostream>
#include <initializer_list>

namespace ssuds
{

	enum class LLIteratorDirection { FORWARD, BACKWARD};

	template <class T>
	class LinkedList
	{
	
	protected:
		class Node
		{
		public:
			T my_data;
			Node* next_node;
			Node* prev_node;

		};

		Node* my_start;
		Node* my_end;
		int my_size;

	public:

		LinkedList()
		{
			my_start = nullptr;
			my_end = nullptr;
			my_size = 0;
		}

		void append(const T& new_value)
		{
			if (my_size == 0)					//if list ine empty
			{
				my_start = my_end = new Node;	//sets start and end both to point to new node
				my_start->my_data = new_value;
				my_start->prev_node = nullptr;
				my_start->next_node = nullptr;
				my_size = 1;
			}
			else
			{
				Node* new_node = new Node;
				new_node->my_data = new_value;
				new_node->prev_node = my_end;
				new_node->next_node = nullptr;

				my_end->next_node = new_node;
				my_end = new_node;
				my_size++;
			}
		}

		void insert(const T& new_value, unsigned int index)
		{
			if (index > my_size)
				throw std::out_of_range("Index out of range");
			else if (index == my_size)
				this->append(new_value);
			//else if (index == 0)
				//call prepend
			else if (index <= (my_size/2))
			{
				Node* cur_node = my_start;
				for (unsigned int i = 0; i < index; i++)
				{
					if (i == index)
					{
						Node* new_node = new Node;
						new_node->my_data = new_value;
						new_node->prev_node = cur_node->prev_node;
						new_node->prev_node->next_node = new_node;
						new_node->next_node = cur_node;
						cur_node->prev_node = new_node;
						my_size++;
					}
					cur_node = cur_node->next_node;
				}				
			}
			else //start at the end of the list and move backwards to the correct index
			{
				Node* cur_node = my_start;
				for (unsigned int i = my_size; i > index; i--)
				{
					if (i == index)
					{
						Node* new_node = new Node;
						new_node->my_data = new_value;
						new_node->prev_node = cur_node->prev_node;
						new_node->prev_node->next_node = new_node;
						new_node->next_node = cur_node;
						cur_node->prev_node = new_node;
						my_size++;
					}
					cur_node = cur_node->prev_node;
				}
			}
		}

		void prepend(const T& new_value)
		{
			//based off append
		}

		unsigned int size() const
		{
			return my_size;
		}

		void output(std::ostream& os) const
		{
			os << "[";
			// This loop is how you loop through the entire linked list
			Node* cur_node = my_start;
			for (unsigned int i = 0; i < my_size; i++)
			{
				os << cur_node->my_data; // this is the line that does whatever with the value we are currently looking at
				cur_node = cur_node->next_node;
				if (i < my_size)
				{
					os << ", ";
				}
			}
			os << "]";
		}

		T& operator[](unsigned int index)
		{
			//check that index is valid
			if (index >= my_size)
				throw std::out_of_range("Index out of range");
			//check if index is > or < the middle index of the list to see if we should start at the end or the beginning (create a function to do this looping method?)
			//loop to proper spot the same way as in output method
			//return data in current node
			else if (index <= (my_size / 2))
			{
				Node* cur_node = my_start;
				for (unsigned int i = 0; i < index; i++)
				{
					if (i == index)
					{
						return cur_node->my_data;
					}
					cur_node = cur_node->next_node;
				}
				}
			else //start at the end of the list and move backwards to the correct index
			{
				Node* cur_node = my_start;
				for (unsigned int i = my_size; i > index; i--)
				{
					if (i == index)
					{
						return cur_node->my_data;
					}
					cur_node = cur_node->prev_node;
				}
				}
		}


		LinkedList(LinkedList && other) //&& means that it is a move constructor
		{
			
		}

		LinkedList(const std::initializer_list<T>& init_list)
		{
			
		}

		LinkedList(const LinkedList& other) //copy constructor
		{
			
		}

		~LinkedList()
		{
			
		}


		void remove(unsigned int index)
		{
			// relatively based off append
		}

		T& at(unsigned int index) const
		{
			//loop through like in the output method
			//check if index is > or < the middle index of the list to see if we should start at the end or the beginning (create a function to do this looping method?)
			//return value
		}


		int find(const T& value_ref, unsigned int start_index = 0) const
		{
			//loop through like in the output method
			//check if index is > or < the middle index of the list to see if we should start at the end or the beginning (create a function to do this looping method?)
			//return index
		}

	
		friend std::ostream& operator<<(std::ostream& os, const LinkedList& A) //similar to output function for the iterator
		{
			
		}

	
		LinkedList& operator=(const LinkedList& other)
		{
			
		}


		// ///////////////////////////////////////////////////////// LLITERATOR SUBCLASS ////////////////////////////////////////////////////////////////////////////////////////////////////
		class LLIterator
		{
		protected:
			Node* current_node;
			LLIteratorDirection my_type;

		public:

			
			LLIterator()
			{
				//set default attributes?
			}

			bool operator!=(const LLIterator& other) const
			{
				//decide how to compare
			}

			const T& operator*()
			{
				//return *this;
			}

			void operator++()
			{
				if (my_type == LLIteratorDirection::FORWARD)
					current_node = current_node->next_node;
				else
					current_node = current_node->prev_node;
			}
		
			void set_reverse(bool rev)
			{
				
			}

		
			LLIterator(const LinkedList* ptr, int starting_index, bool if_reverse)
			{
			
			}

			
			LLIterator operator+()
			{

			}

			bool operator==(const LLIterator& other) const
			{
				
			}

		};

		
		LLIterator begin() const
		{
			//return ? ? ;
		}

	
		LLIterator end() const
		{
			//return ? ? ;
		}

		LLIterator rbegin() const
		{
			
		}

	
		LLIterator rend() const
		{
			
		}

	};
};
