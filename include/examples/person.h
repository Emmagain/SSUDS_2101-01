#pragma once // same as indef/define below, but more efficient
//#indef _PERSON_H_
//#define _PERSON_H_
//these prevent the compiler from ever seeing the declaration of a class more than once

#include <string>

//generally, make attributes private and have methods to INDIRECTLY access them

class Person
{
	//by default, all attributes and methods are private and can onyl be accessed within the class

private:
	// ATTRIBUTES -- a variable that all instances of the class have
	int id;
	std::string first_name;
	std::string last_name;
	float hourly_rate;
	unsigned int hours_worked;

public:
	// CONSTRUCTOR
	Person();

	Person(int starting_id, std::string starting_first_name, std::string starting_last_name);

	//DESTRUCTOR
	~Person();

public:
	// METHODS -- a function that all instances of the class can call
	float calculate_wage();

	int getid();
	std::string getfirst_name();
	std::string getlast_name();
	float gethourly_rate();
	unsigned int gethours_worked();

	void setid(int x);
	void setfirst_name(std::string x);
	void setlast_name(std::string x);
	void sethourly_rate(float x);
	void sethours_worked(unsigned int x);


};
