#pragma once // same as indef/define below, but more efficient
//#indef _PERSON_H_
//#define _PERSON_H_
//these prevent the compiler from ever seeing the declaration of a class more than once

#include <string>

//Make Person part of a namespace

namespace example
{
	/// <summary>
	/// This is a class that illustrates how to use OOP concepts in C++
	/// <summary>

	//generally, make attributes private and have methods to INDIRECTLY access them

	class Person
	{
		//by default, all attributes and methods are private and can onyl be accessed within the class

	private:
		// ATTRIBUTES -- a variable that all instances of the class have
		/// <summary>
		/// This is the (unique) id of this Person
		/// <summary>
		int id;

		/// <summary>
		/// This is the name of this Person
		/// </summary>
		std::string first_name;
		std::string last_name;

		/// <summary>
		/// This is the hourly rate of payment for this Person
		/// </summary>
		float hourly_rate;

		/// <summary>
		/// This is the number of hours this Person has worked.
		/// </summary>
		unsigned int hours_worked;

	public:
		// CONSTRUCTOR

		/// <summary>
		/// This is the "default" constructor that doesn't require parameters
		/// </summary>
		Person();

		/// <summary>
		/// This is the constructor that requires parameters
		/// </summary>
		/// <param name="id"></param>
		/// <param name="first_name"></param>
		/// <param name="last_name"></param>
		Person(int starting_id, std::string starting_first_name, std::string starting_last_name);

		//DESTRUCTOR

		/// <summary>
		/// This is the destructor
		/// </summary>
		~Person();

	public:
		// METHODS -- a function that all instances of the class can call

		/// <summary>
		/// This calculates a Person's wage
		/// </summary>
		/// <returns></returns>
		float calculate_wage();

		/// <summary>
		/// This returns a Person's id number
		/// </summary>
		/// <returns></returns>
		int getid();

		/// <summary>
		/// This returns a Person's name
		/// </summary>
		/// <returns></returns>
		std::string getfirst_name();
		std::string getlast_name();

		/// <summary>
		/// This returns a Person's hourly rate
		/// </summary>
		/// <returns></returns>
		float gethourly_rate();

		/// <summary>
		/// This returns the number of hours a Person has worked
		/// </summary>
		/// <returns></returns>
		unsigned int gethours_worked();

		/// <summary>
		/// This sets a Person's id number
		/// </summary>
		/// <param name="x"></param>
		void setid(int x);

		/// <summary>
		/// This sets a Person's name
		/// </summary>
		/// <param name="x"></param>
		void setfirst_name(std::string x);
		void setlast_name(std::string x);

		/// <summary>
		/// This sets the hourly rate
		/// </summary>
		/// <param name="new_rate"></param>
		void sethourly_rate(float new_rate);

		/// <summary>
		/// This sets the number of hours a Person has worked
		/// </summary>
		/// <param name="x"></param>
		void sethours_worked(unsigned int x);

	};
};
