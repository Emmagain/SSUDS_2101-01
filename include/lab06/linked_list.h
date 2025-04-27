#pragma once

#include <iostream>
#include <initializer_list>

namespace ssuds
{
	//DONE: Total Points - 106
	//  a. (8 points) General structure(attributes, template, nested node class, etc.)
	//	b. (1 points) Size method
	//	c. (8 points) Destructor and clear method
	//	d. (5 points) Append, prepend, and insert methods(these are vital, but we’ll likely do a good bit in class)
	//	e. (5 points) output and << operator
	//	f. (8 points) an iterator - based and an index - based version of find(doing one of these will get you most of the points)
	//  g. (14 points) remove(iterator based and index - based) and remove_all(should use the iterator)
	//	h. (7 points)[] and at methods
	//	i. (7 points) = operator and copy - constructor
	//	j. (7 points) initializer_list and move constructors
	// 
	//	l. (20 points) Iterator support(most of these points are for the “critical” methods for a backwards and
	//		forwards - capable iterator, and a few for some of the semi - optional features like alternate++, +, -, == , - operators)
	//  2. (16 points) Create a new linked_list_tests.cpp test suite in the unit test project. You can probably copy-paste my
	//     test(or yours if it contained thorough enough tests) from ArrayList to use as a starting point.

	enum class LLIteratorDirection { FORWARD, BACKWARD };

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

		LinkedList(const std::initializer_list<T>& init_list)
		{
			my_start = nullptr;
			my_end = nullptr;
			my_size = 0;

			for (T cur_val : init_list)
			{
				append(cur_val);
			}
		}

		LinkedList(LinkedList& other) //copy constructor
		{
			for (unsigned int i = 0; i < other.my_size; i++)
			{
				T value = other[i];
				this->append(value);
			}
		}

		LinkedList(LinkedList&& other) //move constructor
		{
			//steal the identity of other - similar to shallow copy
			my_start = other.my_start;
			my_end = other.my_end;
			my_size = other.my_size;
			//now set other to not point to the list anymore. These new pointers are now the only pointers to the list.
			other.my_start = nullptr;
			other.my_end = nullptr;
			other.my_size = 0;
		}

		~LinkedList()
		{
			Node* cur_node = my_start;
			for (unsigned int i = 0; i < my_size; i++)
			{
				Node* temp = cur_node->next_node;
				delete cur_node; // this is the line that does whatever with the value we are currently looking at
				cur_node = temp;
			}
		}

		void append(const T& new_value)
		{
			if (my_size == 0)					//if list is empty
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
			else if (index == 0)
				this->prepend(new_value);
			else if (index <= (my_size / 2))
			{
				Node* cur_node = my_start;
				for (unsigned int i = 0; i <= index; i++)
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
				Node* cur_node = my_end;
				for (unsigned int i = my_size-1; i >= index; i--)
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
			if (my_size == 0)					//if list is empty
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
				new_node->prev_node = nullptr;
				new_node->next_node = my_start;

				my_start->prev_node = new_node;
				my_start = new_node;

				my_size++;
			}
		}

		void clear() 
		{
			Node* cur_node = my_start;
			for (unsigned int i = 0; i < my_size; i++)
			{
				Node* temp = cur_node->next_node;
				delete cur_node; // this is the line that does whatever with the value we are currently looking at
				cur_node = temp;
			}
			my_start = nullptr;
			my_end = nullptr;
			my_size = 0;
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
				if (i < my_size-1)
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
				for (unsigned int i = 0; i <= index; i++)
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
				Node* cur_node = my_end;
				for (unsigned int i = my_size-1; i >= index; i--)
				{
					if (i == index)
					{
						return cur_node->my_data;
					}
					cur_node = cur_node->prev_node;
				}
			}
		}

		T& at(unsigned int index) const
		{
			if (index >= my_size)
				throw std::out_of_range("Index out of range");
			else if (index <= (my_size / 2)) //start at beginning of list and move forwards to correct index
			{
				Node* cur_node = my_start;
				for (unsigned int i = 0; i <= index; i++)
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
				Node* cur_node = my_end;
				for (unsigned int i = my_size - 1; i >= index; i--)
				{
					if (i == index)
					{
						return cur_node->my_data;
					}
					cur_node = cur_node->prev_node;
				}
			}
		}

		int find(const T& value_ref, unsigned int start_index = 0) const
		{
			//loop through like in the output method
			//check if index is > or < the middle index of the list to see if we should start at the end or the beginning (create a function to do this looping method?)
			//return index
			Node* cur_node = my_start;
			for (unsigned int i = start_index; i < my_size; i++)
			{
				if (cur_node->my_data == value_ref)
					return i;
				cur_node = cur_node->next_node;
			}
			return -1; //means value is not in list
		}

		friend std::ostream& operator<<(std::ostream& os, const LinkedList& A) //similar to output function for the iterator
		{
			A.output(os);
			return os;
		}

		LinkedList& operator=(const LinkedList& other)
		{
			this->clear();
			for (unsigned int i = 0; i < other.my_size; i++)
			{
				T value = other[i];
				this->append(value);
			}
		}

		void remove(unsigned int index)
		{
			// relatively based off append
			// removes the node at a given index
			if (index > my_size)
				throw std::out_of_range("Index out of range");
			else if (index <= (my_size / 2))
			{
				Node* cur_node = my_start;
				for (unsigned int i = 0; i <= index; i++)
				{
					if (i == index)
					{
						Node* previous = cur_node->prev_node;
						Node* next = cur_node->next_node;
						previous->next_node = next;
						next->prev_node = previous;
						delete cur_node;
						cur_node = next;
						my_size--;
						return;
					}
					cur_node = cur_node->next_node;
				}
			}
			else //start at the end of the list and move backwards to the correct index
			{
				Node* cur_node = my_end;
				for (unsigned int i = my_size - 1; i >= index; i--)
				{
					if (i == index)
					{
						Node* previous = cur_node->prev_node;
						Node* next = cur_node->next_node;
						previous->next_node = next;
						next->prev_node = previous;
						delete cur_node;
						cur_node = previous;
						my_size--;
						return;
					}
					cur_node = cur_node->prev_node;
				}
			}
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
				current_node = nullptr;
				my_type = LLIteratorDirection::FORWARD;
			}

			LLIterator(Node* node, LLIteratorDirection direction)
			{
				current_node = node;
				my_type = direction;
			}

			bool operator!=(const LLIterator& other) const
			{
				if (current_node != other.current_node || my_type != other.my_type)
					return true;

				else
					return false;
			}

			bool operator==(const LLIterator& other) const
			{
				if (current_node == other.current_node && my_type == other.my_type)
					return true;

				else
					return false;
			}

			const T& operator*()
			{
				return current_node->my_data;
			}

			Node* get_node()
			{
				return current_node;
			}

			void set_node(Node* new_node)
			{
				current_node = new_node;
			}

			void operator++()
			{
				if (my_type == LLIteratorDirection::FORWARD)
				{
					current_node = current_node->next_node;
				}
				else //if backwards iterator
				{
					current_node = current_node->prev_node;
				}
			}

		};


		LLIterator begin() const
		{
			LLIterator temp(this->my_start, LLIteratorDirection::FORWARD);
			return temp;
		}


		LLIterator end() const
		{
			LLIterator temp(nullptr, LLIteratorDirection::FORWARD);
			return temp;
		}

		LLIterator rbegin() const
		{
			LLIterator temp(this->my_end, LLIteratorDirection::BACKWARD);
			return temp;
		}


		LLIterator rend() const
		{
			LLIterator temp(nullptr, LLIteratorDirection::BACKWARD);
			return temp;
		}

		LLIterator find_it(const T& value_ref, unsigned int start_index = 0) const //iterator-based version of find
		{
			LLIterator it = this->begin();
			int i = 0;
			while (it != this->end())
			{
				if (i >= start_index && *it == value_ref)
				{
					return it;
				}
				i++;
				++it;
			}
			throw std::runtime_error("Value is not in list");
		}

		LLIterator remove_it(LLIterator it) //ITERATOR BASED
		{
			// relatively based off append
			// removes the first node with a given value
			LLIterator temp(this->my_end, LLIteratorDirection::FORWARD);
			if (it == this->begin())
			{
				Node* next = it.get_node()->next_node;  
				next->prev_node = nullptr;
				delete it.get_node();
				it.set_node(next);
				my_start = next;
				my_size--;
				return it;
			}
			else if (it == temp)
			{
				Node* previous = it.get_node()->prev_node;
				previous->next_node = nullptr;
				delete it.get_node();
				it.set_node(nullptr);
				my_end = previous;
				my_size--;
				return it;
			}
			else if (it == this->end())
			{
				return it;
			}
			else
			{
				Node* previous = it.get_node()->prev_node;
				Node* next = it.get_node()->next_node;
				previous->next_node = next;
				next->prev_node = previous;
				delete it.get_node();
				it.set_node(next);
				my_size--;
				return it;
			}
		}

		void remove_all(const T& value_ref) //ITERATOR BASED
		{
			//based on remove/iterator
			//remove every node in the list with the given value
			LLIterator temp(this->my_end, LLIteratorDirection::FORWARD);

			LLIterator it = this->begin();
			if (*it == value_ref)
			{
				Node* next = it.get_node()->next_node;
				next->prev_node = nullptr;
				delete it.get_node();
				it.set_node(next);
				my_start = next;
				my_size--;
			}
			while (it != this->end())
			{
				if (*it == value_ref)
				{
					if (it.get_node() == my_end)
					{
						Node* previous = it.get_node()->prev_node;
						previous->next_node = nullptr;
						delete it.get_node();
						it.set_node(nullptr);
						my_end = previous;
						my_size--;
					}
					else
					{
						Node* previous = it.get_node()->prev_node;
						Node* next = it.get_node()->next_node;
						previous->next_node = next;
						next->prev_node = previous;
						delete it.get_node();
						it.set_node(next);
						my_size--;
					}
				}
				else
				{
					++it;
				}
			}
		}

	};
}
