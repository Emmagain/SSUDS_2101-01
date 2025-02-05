#pragma once
#include <person.h>

namespace example
{
	class PersonDatabase
	{
	private:
		
		/// <summary>
		/// This is a pointer variable that points to the beginning of the array that holds Person objects
		/// </summary>
		Person* my_array_ptr;

		/// <summary>
		/// This is the number of Person objects currently in the array
		/// </summary>
		unsigned int my_array_size;

		/// <summary>
		/// This is the file that the PersonDatabase data will be stored in
		/// </summary>
		std::string my_file_name;

	public:
		//Constructor, should open a file and read in one person per line like this:
		// 101 John Doe 42 13.5
		// 102 Sally Smith 18 19.75

		/// <summary>
		/// This is a constructor that takes one argument, it requires a file name to be given. It will open a file, and read in all the data, 
		/// one Person object per line, then close the file
		/// </summary>
		/// <param name="fname"></param>
		PersonDatabase(std::string fname);

		/// <summary>
		/// This is a constructor that does not require arguments, it creates the PersonDatabase object and sets the array, array size, and array capacity to 0
		/// </summary>
		//PersonDatabase(); 

		/// <summary>
		/// This is the destructor, it writes all the data in the array into the given file, then frees the array
		/// </summary>
		~PersonDatabase(); 

		/// <summary>
		/// This method adds a given Person object to the array
		/// </summary>
		/// <param name="p"></param>
		void add_person(Person p);
		
		/// <summary>
		/// This method removes the Person object with the given id number from the array
		/// </summary>
		/// <param name="remove_id"></param>
		void remove_person(int remove_id);

		/// <summary>
		/// This method returns the number of Person objects currently in the array
		/// </summary>
		/// <returns></returns>
		unsigned int get_num_people();

		/// <summary>
		/// This method returns a string that lists all the information about each Person object in the database, with one Person object per line.
		/// </summary>
		/// <returns></returns>
		std::string to_string();

	};
}